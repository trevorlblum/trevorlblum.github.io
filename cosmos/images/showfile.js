// script using divs 1-15 as targets. Image ids 0-224, 15 per row
// javascript code from file io.html invoked by
// <script type="text/javascript" src="showfile.js"></script>
// and button  <input type="file" onchange="showFile()">
// Check for the various File API support.
   if (window.File && window.FileReader && window.FileList && window.Blob) {
      var freq=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
      function showFile() {
         document.getElementById('caller').innerHTML="show file entered";
         var preview = document.getElementById('show-text');
         var file = document.querySelector('input[type=file]').files[0];
         var reader = new FileReader()
         var textFile = /text.*/;
         var htmlversion='';var words=[];var w=0;var p=0;
         var x=new Image(30,30);
         var space=new Image(10,25);space.id='space';space.src='space10x25.png';
         if (file.type.match(textFile)) {
            reader.onload = function (event) {
               htmlversion=event.target.result.replace(/\n/g,"\t");
                words=htmlversion.split("\t");
               for(p=0;p<words.length;p++){
                 freq[parseInt(words[p])]+=1;
                 if(words[p]=='0')words[p]='black';
                }
               for(dv=0;dv<15;dv++){
                 for(p=dv*15;p<(dv+1)*15;p++){
                    x=new Image(30,30);x.id=p;x.src=words[p]+'.png';
                    document.getElementById('div'+(dv+1)).appendChild(x);
                  }
                }
                var frequencies="black="+freq[0]+", ";
                for(p=1;p<27;p++)frequencies+=p+"="+freq[p]+", ";
                document.getElementById('divt').innerHTML=frequencies;//"<br>ABCDEFGHIJKLMNOPQRSTUVWXYZ<br>"+freq+"<br><br>";//write the frequencies
               }
            } 
            else 
            {
             preview.innerHTML = "<span class='error'>It doesn't seem to be a text file!</span>";
            }
           reader.readAsText(file);
          }
        } 
        else 
        {
          alert("Your browser is too old to support HTML5 File API");
        }
