/* 20/3/2022 fixed screen display - javascript fails on font
 revisited 19/3/2022 - filename must be URL.
 cut-down to just display cosmos_puzzle.png. 
 Printwriter not supported in javascript
 original now as cosmos_pde.pde
 data width and height do not set cell width in javascript but do in the pde version (line 18 - kludge )
*/
int rowints[]={13,8,12,9,3,21,22,3,0,23,13,7,22,7,21};
String filename="https://trevorblum.name/cosmos/cosmos_puzzle.png";
PImage data;
PImage[] cell,display;
int cellwidth=0,cellheight=0,d=0, pcount=0;
int [] ccount=new int[26];

void setup(){
 size(900,925); 
 frameRate(2);
  data=loadImage(filename);
//  cellwidth=(data.width/15)+5;// only works in .pde, not in javascript
  cellwidth=61;
  cellheight=cellwidth;
// start - extract pixels from rects into cell  
  cell=new PImage[15];
  display=new PImage[15];
  for(int i=0; i<15;i++){ 
    ccount[i]=0;
    cell[i]=createImage(cellwidth,cellheight,RGB);
    display[i]=createImage(cellwidth,cellheight,ARGB);
// colour each cell with transparency to see coverage area    
    pcount=0;
   for(int p=0;p<cell[i].height;p++){
     for(int w=0;w<cell[i].width;w++){
        pcount+=1;
        cell[i].set(w,p,color(data.get(w+i*(cellwidth),p),6));//positive display
        display[i].set(w,p,color(0)-data.get(w+i*(cellwidth),p));//negative display
// select window within cell
        if(p>3&&p<30&&w>5&&w<40){
          if(data.get(w+i*((data.width/15)-1)+10,p+9)==-16777216)ccount[i]+=1;
        }
     }
    }
  }
}
void draw(){
 image(data,0,0); 
 if(d>=data.width-cellwidth-25)d=0;else d=d-1+(data.width/15);{
 noFill();stroke(0,0,255);strokeWeight(3);rect(d+10,7,cellwidth,height-95);}
 for(int p=0;p<15;p++){
    image(cell[p],p*cellwidth,height-85);
    image(display[p],3+p*cellwidth,height-45);
  }
}
void mousePressed(){
  saveFrame("/users/trevorblum/documents/processing/cosmos/savedframe.png");
//    noLoop();
}
void mouseReleased(){
//  loop();
}
