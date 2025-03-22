/* 
 11/3/2022 WIP tidying up positions on screen 
 10/3/2022 modified reference grid cells for siemens actuals. Added strip cells column
 WIP get scanpatches positions right
 18/2/2022 WIP match chart positions as charty table-done
 22/2/2022 simplified to only do Siemens 10SG
 WIP scanpatches and add strip to image and get x coordinates right
*/
PImage Piccy;
int Sizex=0,Sizey=0,Scale=0;
int xoff=1,yoff=40,rxoff=239,ryoff=22;
boolean one=false;
int nrows=10,ncols=7;
PVector  Whitexy,Whitewh;
PImage Barcode;
int [] strip;
PVector [][] ref;
String Siemens_name="Multistix-Urinalysis-Color-Key.png";
int [] charty={96,177,257,349,422,523,593,684,766,872};

void setup(){
  size(920,800);
//  frameRate(.4);
  strokeWeight(3);
//  PVector [] Whitexy;
//  PVector [] Whitewh;
  strip=new int [nrows];
  ref=new PVector [ncols][nrows];
  Barcode=loadImage("Siemens teststrip.bmp");

  Piccy=loadImage(Siemens_name);//+strip.png");
  Scale=1050*Piccy.width/950;//                 why 811?
  surface.setResizable(true);
  Sizex=Piccy.width;Sizey=Piccy.height;
  Whitexy=new PVector(10,87*Scale/950);
  Whitewh=new PVector(64,69);
  println(Whist());//print white patch r,g,b colours
 // WBgram();//average over white patch in bin(=10) bins.
  setlocations();
  scanpatches();
  checkstrip();
}


void draw(){
background(0,0,255);
image(Piccy,0,0,Scale,Scale);
drawgrid();
image(Barcode,width-Barcode.width/3-10,height-Barcode.width/3-10,Barcode.width/3,Barcode.height/3);
 for(int i=0;i<nrows;i++)for(int x=0;x<ncols;x++)ellipse(20+rxoff+x*82,.85*ref[x][i].y,15,15);
//setlocations();
//check_strip();
}

void drawgrid(){
  noFill();
//references  
   for(int y=0;y<10;y++)for(int x=0;x<500;x+=82){
//     line(x+rxoff,0,x+rxoff,800);
     rect(x+rxoff,charty[y]*.85+5,40,25); 
   }
   //strip
   for(int y=0;y<10;y++){
//     line(xoff,0,rxoff,800);
     rect(xoff,charty[y]*.85+5,40,40); 
   }
//     stroke(0,255,0);strokeWeight(3);rect(Whitexy.x,Whitexy.y,Whitewh.x,Whitewh.y);
}



PVector Whist(){ //get max of white patches for balance
  PVector c=new PVector(0,0,0);
  color cc;
  for(int x=0;x<Whitewh.x;x++)for(int y=0;y<Whitewh.y;y++){
   cc=Piccy.get(x,y);
   if(red(cc)>c.x)c.x=red(cc);//maximum red 
   if(green(cc)>c.y)c.y=green(cc);//maximum green 
   if(blue(cc)>c.z)c.z=blue(cc);//maximum blue
  }
  println("Max whites ",c);
 
  return c;
}

void WBgram(){//print colour averages over white balance area
  color cc;
  int bin=7,bin2=bin*bin;;// bin size to fit wxh on Processing console screen
  int [] ccbinr = new int [int(Whitewh.x*Whitewh.y)/bin2];
  int [] ccbing = new int [int(Whitewh.x*Whitewh.y)/bin2];
  int [] ccbinb = new int [int(Whitewh.x*Whitewh.y)/bin2];
  for(int x=0;x<Whitewh.x;x+=bin)for(int y=0;y<Whitewh.y;y+=bin){
   for(int bx=0;bx<bin;bx++)for(int by=0;by<bin;by++){
     cc=Piccy.get(int(Whitexy.x+bx),int(Whitexy.y+by));
     if(red(cc)>ccbinr[(x*y)/bin2])ccbinr[(x*y)/bin2]=int(red(cc)); 
     if(green(cc)>ccbing[(x*y)/bin2])ccbing[(x*y)/bin2]=int(green(cc)); 
     if(blue(cc)>ccbinb[(x*y)/bin2])ccbinb[(x*y)/bin2]=int(blue(cc)); 
    }
  }
  for(int b=0;b<ccbinr.length;b++){if(b%7==0)println(); print(ccbinr[b],ccbing[b],ccbinb[b],"_");}
}

void scanpatches(){ // pick up strip patch, scan l-r for match, tag match
  PVector tstrgb=new PVector(0,0,0);
  PVector refrgb []=new PVector[nrows];
  int rix=0,y=0; // row index (0-nrows)
  for(int r=0;r<nrows;r++) refrgb[r]=new PVector(0,0,0);
    for(int i=0;i<nrows;i++){
//      for(int i=0;i<nrows;i++)for(int x=0;x<ncols;x++)ellipse(20+rxoff+x*82,.85*ref[x][i].y,15,15);//in draw
      y=charty[i];
      tstrgb.x=0;tstrgb.y=0;tstrgb.z=0;
      println("first strip spot",red(Piccy.get(xoff,y+yoff)),green(Piccy.get(xoff,y+yoff)),blue(Piccy.get(xoff,y+yoff))," at ",xoff,y+yoff);
      for(int px=0;px<20;px++)for(int py=0;py<20;py++){//row test strip average
       tstrgb.x+=red(Piccy.get(xoff+px,py+y+yoff)); 
       tstrgb.y+=green(Piccy.get(xoff+px,py+y+yoff)); 
       tstrgb.z+=blue(Piccy.get(xoff+px,py+y+yoff)); 
      }
//    for(int x=0;x<800;x+=80){//get row reference cell averages
         for(int px=0;px<20;px++)for(int py=0;py<20;py++){//row test strip average
         refrgb[rix].x+=red(Piccy.get(px+rxoff,y+py+yoff)); 
         refrgb[rix].y+=green(Piccy.get(px+rxoff,y+py+yoff)); 
         refrgb[rix].z+=blue(Piccy.get(px+rxoff,y+py+yoff)); 
 //       }
      }
    println("Average strip patch rgb's row - strip ",rix,int(tstrgb.x/400),int(tstrgb.y/400),int(tstrgb.z/400)," ref ",int(refrgb[rix].x/400),int(refrgb[rix].y/400),int(refrgb[rix].z/400));
    rix+=1;
  }
}

void setlocations(){//set strip0,strip1,ref0,ref1 patch locations of original images   
//set strip y locations
fill(0);
  for(int y=0;y<nrows;y++){strip[y]=yoff+y*Sizey/nrows;
//      println (" strip0 y",y," is ","red ",red(Piccy[0].get(75,strip0[y])));
    }
//set reference x and y locations for colour patches of original images   
  for(int x=0;x<ncols;x++)for(int y=0;y<nrows;y++){
    ref[x][y]=new PVector();
    ref[x][y].x=rxoff+x*83;//(Size0x-rxoff+10)/n0cols;
    ref[x][y].y=ryoff+charty[y];//(Size0y-ryoff+50)/n0rows;
//    rect(ref0[x][y].x*Scale,ref[x][y].y*Scale,5,5);
//    println("ref locations ",x,y,ref[x][y].x,ref[x][y].y);
  }
 }

void checkstrip(){//check to see that the strip area is not empty (0,0,0 if transparent - >250,250,250 white??
//  for(int y=0;y<nrows;y++){strip[y]=yoff+y*Sizey/nrows;
  int x=10,y=912;
  if(blue(Piccy.get(x,y))>250){
//        if(red(Piccy.get(75,strip[y]))==0 && green(Piccy.get(75,strip[y]))==0 && blue(Piccy.get(75,strip[y]))==0)
        {println (" test strip not present ");
        fill(255);textSize(30);text(Siemens_name+" test strip empty stopping",130,height-50);noLoop();
   }
 }
}

void Histogram(){ //show colour distribution over image
  
}
void mousePressed(){
  saveFrame("Test_stripper##.png");
}
