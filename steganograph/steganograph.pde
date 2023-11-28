/* Steganograph reads a text file and random;y replaces 3LSB's in colours in an image's pixels
 It uses a unique random generator to place and later to regenerate the text.
 28/11/2023 reviewed for transfer to javascrip browser app.
 
 18/12/2021 lineplaces and coords issue for various file sizes still unresolved.
 Added readback to screen of last 90 lines of recovery file
17/12/2021 WIP -lineplaces & coords. Recovery now working! No errors on two files
 line 33 - lineplaces kludge required - 1+ for lorem ipsum(3324) and logins.csv(13232), 4+for Mail defaults(51184KB)
Mail defaults list gives errors - out-of-bounds unless line 26 kludged
 Seeded random recoverable data from image colors works - tested with files up to 25KB
 */

PImage img;
PrintWriter recovered; 
String filename="900x900.png";
byte [] bytesin;
String [] filein;
int ptr=0;
int seed=12345;//31;//317;//7391 works ok too!
int [][]xcoords;
int lineplaces=50;
int coordstep=18, coordjitter=20;//for lineplaces=50
boolean showlocs=false;// show white spots at substitution positions
boolean showwrite=true;//false;//show readback

String name="logins.csv";//"lorem ipsum.txt";//"Mail defaults list.txt";//);

void setup() {
  size(900, 900);
  randomSeed(seed);
  bytesin=loadBytes(name);
  recovered=createWriter(name+"_Recovery.txt");
  //  println("Input text : "); for(int p=0;p<bytesin.length;p++)print(char(bytesin[p]));
  println("\nbytes read ", bytesin.length);
  img=loadImage(filename);
  surface.setTitle(name);
  lineplaces=1+int((float(bytesin.length)/img.height));//4+kludge for file size 25592bytes else errors
  coordstep=(img.width/lineplaces);
  coordjitter=((img.width)/lineplaces);
  xcoords=new int [lineplaces][img.height];// estimate of xcoords array based on points per line 
  if(lineplaces*img.height<bytesin.length)println("size error ",lineplaces*img.height,bytesin.length);

  randomRecursive(img.height);//exit(); // generate lineplacesxheight values
  println("\nx-based random set lineplaces x imgheight ", lineplaces, "x", img.height, "coordstep", coordstep, "coordjitter", coordjitter);
}

void draw() {
  color ct, c;
  int xrnd, yrnd;
  int ptr=0;
  int xstep=coordstep;//img.width/lineplaces;
  for (int y=0; y<img.height; y++) {
    for (int x=0; x<img.width; x+=xstep) {
//        img.set(x,y,color(img.get(x,y))); //unchanged image pixels -redundant
      if (ptr<bytesin.length) {  //only generate as many points as text chars
//        println("X",x,"xstep",xstep,"X/xstep",x/xstep);
        xrnd=xcoords[x/xstep][y];                              // errors on out-of-bounds for x/xstep =59 - lineplaces=58
        yrnd=y;    // we need 50 steps - width/18
//          if(y==0){print(xcoords[x/xstep][y],"\t");}
        ct=color(img.get(xrnd, yrnd));//,color(img.get(x,y)),bytesin[ptr]);
        c=color(((((ct&0xF80000)>>16)&0xF8)|((bytesin[ptr]>>5))&0x07), (((((ct&0x00F800)>>8)&0xF8)|(bytesin[ptr]>>2)&0x07)), (int(blue(ct))&0xF8)|(bytesin[ptr]&0x03));
        img.set(xrnd, y, c);
       if(showlocs){ img.set(xrnd+1, y, 255);img.set(xrnd+2, y, 255);}//false whites for location.
      }
      ptr+=1;
    }
  }
  image(img, 0, 0, width, height);
  //    fill(255); for(int pt=0;pt<bytesin.length;pt++){int y=pt/10; text(char(bytesin[pt]),(pt*10)%width,10+(y*600)/height);} 
  noLoop();
  recover();
  if(showwrite)readback();
}

void recover() {
  int rec=0, ptr=0, errcnt=0;
  int xrnd, yrnd;
  color c;
  randomSeed(seed);
  println("\nReconstruction from image");
  for (int y=0; y<img.height; y++) {
    for (int x=0; x<img.width; x+=coordstep) {//<lineplaces;x++)
      xrnd=xcoords[x/coordstep][y];
      yrnd=y;
      //      xrnd=int(random(img.width));yrnd=int(random(img.height));
      //--      if(rcheck[xrnd][yrnd]==2){xrnd=int(random(img.width));yrnd=int(random(img.height));}//two-step
      c=img.get(xrnd, y);//int(xrnd),int(yrnd));
      if (ptr<bytesin.length) {
        //      fill(255);rect(int(xrnd),int(yrnd),2,2);
        rec=((((c&0xFF0000)>>16)&0x07)<<5)|((((c&0x00FF00)>>8)&0x07)<<2)|(int(blue(c))&0x03);
        //      if((x%50==0 && ptr<20)){
        //        print("rec= ",hex(rec,2),char(rec)," ",hex(c&0x00FFFFFF,6)," "); 
        //        println((((c&0xFF0000)>>16)&0x07),(((c&0x00FF00)>>8)&0x07),(int(blue(c))&0x03));
        //      }
        recovered.print(char(rec));
        if (rec!=bytesin[ptr]) {
          print(" ERROR ", char(bytesin[ptr])+"->"+char(rec), " ");
          errcnt+=1;
        }
        ptr+=1;
      }
    }
  }
  println("\nEnd Reconstruction Byte count ", ptr, " Error count ", errcnt);
  recovered.flush();recovered.close();
}

void randomRecursive(int lines) { //generate filtered randoms with no duplicates using recursion
  int [] coord=new int[lineplaces];
  boolean dup=false, OK=false;
  randomSeed(seed);
  //space out 50 coordinates within 900 pixel line-step=18
  for (int y=0; y<lines; y++) {
    for (int i=0; i<lineplaces; i++) { //get next uniquecoordinate
      //       coord[i]=18*i+int(random(20));
      while (!dup) {
        coord[i]=coordstep*i+int(random(coordjitter));
        dup=true;
        for (int j=0; j<i; j++)if (coord[i]==coord[j]) {
          dup=false;//loop if exists and is not 0
        }
      }
      dup=false;
    }
    for (int xc=0; xc<lineplaces; xc++)xcoords[xc][y]=coord[xc];
    //         if(y<10){println("\ncoords sample line ",y);
    //         for(int xc=0;xc<lineplaces;xc++)print(xcoords[xc][y]," "); }
  }
  println("xcoords ", lineplaces*lines);
}

void readback(){
  filein=loadStrings(name);
  int ptr=0;
  for(int i=filein.length-90;i<filein.length;i++) text(i+" "+filein[i],10,10*(ptr++));
}

void mousePressed() {
  saveFrame("corruptimage##.png");
}
