//SOURCE.js replaces all javascript code previously in .html body
//generateTextFileUrl(data);

// 16/7/2024 function check_nclick still failing to show redX

const canvas=document.getElementById('canvas');
const context=canvas.getContext('2d');
context.fillStyle='blue';
var replace=0; // holds alpha id for num click replacement
var img=new Image(30,30);
var data=matrixdata.split("\t");// needs terminal tab to get all elements
var english=efreq.split(",");
var solutiontext="";
chartfreqs();
showmatrix();
aclick_from_r=0;

function loaded(){
//document.getElementById("index").innerHTML+="<br>body loaded";
}
 
//routine to look if all number line is now alphas
function checkfinished(){
 var alldone="OK";
 var im="";
 for(i=1;i<27;i++){
    im= document.getElementById('n'+i).src;
// now does number line have any number not replaced? 
    if(im.includes("images/"+i+".png"))       //is there a number left?
      { 
//       document.getElementById('matrix').innerHTML+="N at "+i+" "; // any number remaining show on doc
       alldone="NotYet";
       return false;
      }
//    if(im.includes("clues"))document.getElementById('matrix').innerHTML+="Clue at "+i+" ";//ignore clues as setting
    }
   if(alldone=="OK"){
//    document.getElementById('matrix').innerHTML+="<br>"+"ALL DONE"; 
    document.getElementById('welldone').innerHTML="<img src='images/welldone.png'>";
//  now show solution against 'answer' from text file
//    document.getElementById('matrix').innerHTML+="<br>"+answer;
    return True;
    }
  }


function showmatrix(){               // fill data matrix from .txt file by assembling 15x15 text to .innerHTML
var text="<div class='matrix'>";                                                 // fill with alphabit numeric image[data[i]] 
var tc=0;
  for(i=0;i<data.length;i++){
   if(data[i]==0) text+="<img id='d"+i+"' src=images/black.png>";                // black dividers on matrix from 0( ie 1-26 ) in data
      else 
    if(data[i]<27)text+="<img id='d"+i+"' src=images/"+data[i]+".png>";          // show data file entries (1-26)
             else text+="<img id='d"+i+"' src=images/alphabit"+data[i]+".png>";  // show chosen clues
    if((i%15)==14)text+="<br>";                                                  // new line every 15 entries 
  } 
  //  text="<div class='content' align='left' ><img src=images/showplot.png onclick='chartfreqs()' ><img  src='images/showmatrix.png' onclick='showmatrix()' ></div>"+text;
    document.getElementById('matrix').innerHTML="<br>"+text;                    // fill matrix element with text from above code
    for(i=1;i<27;i++)document.getElementById('n'+i).src="images/"+i+".png";     //on show matrix reset number line
    showclues();
    //solutiontext="solution"+text+"solution end";   //build solution text as data
}

function showclues(){//place the given clues as alpha on the number line
var c=clues.split(",");
for(i=1;i<27;i++){
  for(cl=0;cl<c.length;cl+=2)if(i==c[cl+1]){
     document.getElementById('n'+i).src="images/dark/alphabit"+c[cl]+".png";//replace number line element by alpha clue (greyed)
     document.getElementById('n'+i).src="images/clues/"+c[cl]+".png";//replace alpha line element by alpha clue (greyed)
    }
  }
  for(i=0;i<data.length;i++){
    for(cl=0;cl<c.length;cl+=2)if(data[i]==c[cl+1])data[i]=c[cl];//replace data element by alpha clue (9 becomes "M")
  }
}

function drawBar(ctx, upperLeftCornerX, upperLeftCornerY, width, height,color){
    ctx.save();
    ctx.fillStyle=color;
    ctx.fillRect(upperLeftCornerX,upperLeftCornerY,width,height);
    ctx.restore();
}

function calcfreqs(){                                              // get letter frequencies
for(i=0;i<26;i++)freq[i]=0;
for(i=0;i<data.length;i++) if(data[i]!=0)freq[parseInt(data[i])-1]+=1;
}

function chartfreqs(){                                            //display frequencies and charts
var textnums="";
var textalphs="";
var c=clues.split(",");

calcfreqs();
context.lineWidth=2;
context.beginPath();context.moveTo(5,255-5*freq[0]);
for(i=0;i<freq.length;i++){
context.lineTo(17+(i)*30,255-5*freq[i]);
//img=new Image(30,30);
//img.id='i+1';img.src=images/i+1+'.png';
drawBar(context,3+i*30,255-5*freq[i],30,5*freq[i],'#CCCCDD');
context.font = "bold 15px Arial";
context.fillStyle="#0000ff";
context.fillText(freq[i],12+i*30,250-5*freq[i]);
//document.getElementById('div1').appendChild(img);//add <img 1-26> in javascript not provide 'onclick' with new images
 textnums+="<img id='n"+(i+1)+"' src='images/"+(i+1)+".png' onclick='nclick("+(i+1)+")' >";
 var source="alphabit"+String.fromCharCode(65+i)+".png";
 textalphs+="<img id='a"+(i+1)+"' src='images/"+source+"' onclick='aclick("+(i+1)+")' >";
 context.stroke();
 }
document.getElementById('div1').innerHTML=textnums+"<br>"+textalphs;
// now plot english comparison data
context.beginPath();context.moveTo(5,100-5*english[0]);
context.fillStyle="#ffaaaa";
context.strokeStyle="#ffaaaa";
context.fillText("English frequencies A-Z %",5,20);
context.fillStyle="#0000ff";
context.fillText("This matrix",5,135);
context.fillStyle="#ffaaaa";
for(i=0;i<english.length;i++){
context.lineTo(15+(i)*30,100-5*english[i]);
context.fillText(String.fromCharCode(i+65),5+i*30,100);
}
context.moveTo(5,105);context.lineTo(canvas.width,105);
context.stroke();
showclues();
}


function nclick(){                                                //click on number in row - replace image with alpha choice
 //replace==0 means no previous 'a' click, so clear the target and its 'a'
    var tmp=(document.getElementById('n'+arguments[0]).src);      //tmp is full url   
   if(tmp.substring(tmp.length-11,tmp.length-6)!="clues")         // don't touch clues in 'n' line
   {
    tmp=tmp.charAt(tmp.length-5);                                //n line 9 may be X, so we want to replace a line 'x'-64
    if(intFromAlpha(tmp)>64) {                      // there was an alpha image at the clicked point, so do the reset things. Avoids error in unset case
       tmp=intFromAlpha(tmp)-64;                    //gets ordinal position
        document.getElementById('a'+tmp).src="images/alphabit"+String.fromCharCode(64+tmp)+".png";   //restore alpha image in alpha line at ordinal
        document.getElementById('n'+arguments[0]).src="images/"+arguments[0]+".png";                 //reset number line
       for(i=0;i<data.length;i++)
        if(data[i]==arguments[0])document.getElementById('d'+i).src="images/"+arguments[0]+".png";   //reset matrix   
        }
     if(replace!=0){
      var tmp=document.getElementById('n'+arguments[0]).src;                                         //tmp is full url   
      if(tmp.substring(tmp.length-11,tmp.length-6)!="clues")
        { // don't touch clues in 'n' line
          document.getElementById('n'+arguments[0]).src="images/alphabit"+String.fromCharCode(64+replace)+".png";
        }
      for(i=0;i<data.length;i++) //replace matrix element with alpha
        if(data[i]==arguments[0])document.getElementById('d'+i).src="images/alphabit"+String.fromCharCode(64+replace)+".png";
     }
  }
  replace=0;
  nclick_to=arguments[0]-1; //set destination on replacement
//  check_nclick();
  checkfinished();
  }

  // check finished exit

// function to enable backtrack from alpha name to ordinal in alpha choice line
function intFromAlpha(alpha){
var ret;
for(i=64;i<91;i++)
if(alpha==String.fromCharCode(i))ret=i;
return ret;
}

function aclick(){              //click on alpha in row - set id for num to use as replacement - needs to be fixed for set clue in 'a' line
var tmp="";
var found="false";
replace=arguments[0];
var cmp=String.fromCharCode(64+arguments[0]);// e.g. 19  replace=arguments[0];
var clue=tmp.substring(tmp.length-11,tmp.length-6)!="clues";
 for(i=1;i<27;i++)
  {
  tmp=document.getElementById('n'+i).src;                //number or alpha in top line?
  tmp=tmp.substring(tmp.length-13,tmp.length-5);         //is this an alphabit?
  if((tmp=="dark" || clue=='clues')==false){                  // alphabit or clue - leave it alone
     tmp=document.getElementById('n'+i).src;             //get name again for alpha ID match
     tmp=tmp.substring(tmp.length-5,tmp.length-4);       // alpha ID extracted
     if(tmp==cmp)
      {   
        found="true";replace=0;
      }
   }
 }
 if(found=='false'){
     document.getElementById('a'+arguments[0]).src="images/dark/alphabit"+String.fromCharCode(64+arguments[0])+".png";
     aclick_from=cmp; // set source on replacement
     aclick_from_r=replace
}
}

function nref(){                                       //return 1 or 2 digit numeric reference
var nref=arguments[0]; var res=0;
tmp=nref.substring(nref.length-6,nref.length-5);//10-26
if(tmp=="/") res=nref.substring(nref.length-5,nref.length-4);else 
res=nref.substring(nref.length-6,nref.length-4);
return res;
}

function nrefToAref(){                             //replace numeric index with alpha equivalent
var nref=arguments[0]; var res=0;
tmp=nref.substring(nref.length-6,nref.length-5);//10-26
if(tmp=="/") res=nref.substring(nref.length-5,nref.length-4);else 
res=nref.substring(nref.length-6,nref.length-4);
var aref=String.fromCharCode(64+res*1);
return aref;
}

function listclues(){                            // display set clues
   document.getElementById('clues').innerHTML+="<h3>You have a clue to begin with "+clues+"</h3>";
}

function moreclues(){                            // increment clue display cluecount
if(cluecount<extras.length*2)clues+=","+extras[cluecount-1]+","+extras[cluecount];
//window.alert(clues);
cluecount+=2;
chartfreqs();
showmatrix();
}


//write solutiontext to solution.txt file

function writesolution(){
  document.getElementById('div1').innerHTML="abcdefgh";//getElementById('matrix').innerHTML;
}

function showanswer(){
if(answer!=null){              // if no answer in text file, skip this bit
var letters=answer.split(","); // answer comes from .txt file

 }
document.getElementById('div_answer').innerHTML="";
 for(a=1;a<27;a++)//a==1, is 'U' which is pngs/21
  {
    for(l=0;l<26;l++){
      ll=l+1;
      if(letters[l*2+1]==a)
      {
        x="images/A_Z.pngs/"+ll+".png";
        document.getElementById('div_answer').innerHTML+="<img src="+x+" onclick='clearanswer()'>";
      }
    }
  }
    document.getElementById('div_answer').innerHTML+="<br>";

 for(a=1;a<27;a++)
  {
     x="images/"+a+".png";
     document.getElementById('div_answer').innerHTML+="<img src="+x+" onclick='clearanswer()'>";   
  }
}

function clearanswer(){
    document.getElementById('div_answer').innerHTML="";
}

function check_nclick(){              //check if nclick(num) and aclick(alfa) match answer

source=aclick_from_r;
dest=1+nclick_to;

  //clear nclick image
//    if(document.getElementById('n'+(dest)).src=="images/wrongX.png"){
//      document.getElementById('n'+(dest)).src="images/A_Z.pngs/"+source+".png";
//     }
// aclick 20 nclick 15
//window.alert("source=  "+source+" dest= "+dest); // number of choice, alpha of choice

// does replace match answer at [2*alfanum]
ans=answer.split(",");

//from 19 answer_to 21 ie should be 21, is 19 which should show redX
window.alert("answer from "+(dest) +" answer_to "+ans[2*source-1]);

if(dest!=ans[2*source-1]){
    window.alert("Mismatch dest= "+dest+" answer_dest= "+ans[2*source-1]);
    document.getElementById('n'+(dest)).src="images/wrongX.png"; // src replaced, onclick unchanged


    }
//    else document.getElementById('a'+(nclick_from)).src="images/A_Z.pngs/"+nclick_from+".png";

// need to show original number in matrix not alpha substitute when errored.    

}

