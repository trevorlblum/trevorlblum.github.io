/*
25/4/2025 updated Combur names for dropzone. see line 87
Strip charts : Dimensions of varieties.

Combur 10: Combur basic 5 test columns, 10 tests
10 tests, 5 values 60x50 pixel islands 70x75 separation
Image size 511x850

Siemens 10:
10 tests, 7 Values, 65 X, 70 Y separation
test strips separation 7mm total length 75mm
45x28 Islands
Image size 660x850

Livingstone 10 :
As for siemens.
35x40 islands
*/


numoftests=[10,10,10]; //roche 10 //1/5/2025
//ntests=numoftests[test_num];
ref_image_src=["reference_images/Combur9.png","reference_images/Siemens10.png","reference_images/Livingstone10.png"];

// manufacturer,number of tests,number of test values,tlc spacing
multi_test=["Combur,10,5,50,50,60,70","Siemens,10,7,45,28,65,70","Livingstone,10,7,35,40,65,70"];

/*Combur Comburalt Siemens Livingston*/

diags=[["Leukocytes	:neg:1+:2+:3+:.:",
"Nitrite	:neg:pos:",
"pH	        :5:6:7:8:9",
"Protein	:neg:1+:2+:3+:.:",
"Glucose	:normal:1+:2+:3+:5",
"Ketones	:neg:1+:2+:3+:.:",
"Urobilogen	:normal:1+:2+:3+:4+",
"Bilirubin	:neg:1+:2+:3+:.:",
"Blood		:neg:1+:2+:3+:4+",
"Haemoglobin	:.:1+:2+:3+:4+"],

["LEU	:negative:,:,:trace:small:moderate:large:",
"NIT	:negative:.:.:.:positive:positive:",
"URO	:normal:normal:.:.:2:4:8:",
"PRO	:negative:trace:.:30:100:200:2000",
"pH	:5.0:6.0:6.5:7.0:7.5:8.0:8.5",
"BLO	:negative:trace:moderate:tace:small:moderate:large",
"SG	:1.000:1.005:1.010:1.015:1.020:1.025:1.030",
"KET	:negative:.:trace:small:moderate:large:large",
"BIL	:negative:.:.:.:small:moderate:large",
"GLU	:negative:.:100:250:500:1000:2000"],

["Leucocytes       :0neg:. :. :15trace:70+:125++:500+++:", 
"Nitrite          :neg:. :. :. :Positive:Positive:Positive:",
"Urobilinogen     :0.2normal:16Normal:.:.:33umol/L:66umol/L:131umol/L:",
"Protein          :neg:trace:.:0.3g/L:1++:3+++:>20++++:",
"pH               :5.0:6.0:6.5:7.0:7.5:8.0:8.5:",
"Blood            :neg:Trace10:Moderate80:trace:small25:moderate60:large200:",
"Specific Gravity :1.000:1.005:1.010:1.015:1.020:1.025:1.030:",
"Ketone           :neg:.:0.5mmol/L:1.5mmol/L:4mmol/L:8mmol/L:16mmol/L:",
"Bilirubin        :neg:. :. :. :small+:moderate++:large+++:",
"Glucose          :neg:.:trace5.5mmol/L:14mmol/L:28++mmol/L:55+++mmol/L:>=111++++mmol/L:"]];


rochediags=[1,2,5,4,7,3,8,6,9];                                    // WIP 24/4

//spaceing for manufacturers must be set for each one ( current is 3 )
refspacing=[60,79,79];//vertical spacing on reference
refhorspacing=[70,82,82];//horizontal spacing on reference


//namelist for manufacturers
namelist=[["Leuk(c)cytes","Nitrit(e)os)","pH","Protein","Glucose","Keton(es)","Urobilinogene","Bilirubine","Blood","Haemoglobin"],

["LEU","NIT","URO","PRO","pH","BLO","SG","KET","BIL","GLU"],

["Leucocytes","Nitrite","Urobilinogen","Protein","pH","Blood","Specific Gravity","Ketone","Bilirubin","Glucose"]];

//tlc_Roche.tlc_roche_alt.tlc_Livingstone.tlc_Siemens
multi_tlc=[ [120,25,250,95,250,160,250,230,250,300,250,370,250,445,250,510,250,585,250,650,310,720],

[170,75,240,150,240,220,240,310,240,375,240,465,240,525,240,605,230,680,240,785],

[130,30,136,110,130,200,136,290,136,360,136,450,136,542,136,624,115,710,120,790]];