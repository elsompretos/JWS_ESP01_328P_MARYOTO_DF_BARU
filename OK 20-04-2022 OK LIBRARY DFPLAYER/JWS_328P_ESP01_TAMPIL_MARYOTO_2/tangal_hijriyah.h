
const char namaBulanHijriyah[][15] PROGMEM = {"Muharram", "Safar", "Rabiul-Awal", "Rabiul-Akhir", "Jumadil-Awal", "Jumadil-Akhir", "Rajab", "Syaban", "Ramadhan", "Syawal", "DzulQaidah", "DzulHijjah"};

byte hari_besar;

String Kuwaiti_algorithm (double tanggalH, double bulanH, double tahunH, int hariH, double adj_hij){
  
  tanggalH = tanggalH - adj_hij;

  String res_kalHij;
  
  double m = bulanH;
  double y = tahunH;

  if(m<3) {
    y -= 1;
    m += 12;
  }
  double a = floor(y/100.);
  double b = 2 - a + floor(a/4.);
  
  if(y<1583) {
    b = 0;
  }

  if(y==1582) {
    if(m>10)  b = -10;
    if(m==10) {
      b = 0;
      if(tanggalH>4) b = -10;
    }
  }

  double jd = floor(365.25*(y+4716))+floor(30.6001*(m+1))+tanggalH+b-1524; // CARA 1
  //uint32_t jd = floor(365.25*(y+4716))+floor(30.6001*(m+1))+tanggalH+b-1524; // CARA 2

  b = 0;

  if(jd>2299160){
    a = floor((jd-1867216.25)/36524.25);
    b = 1 + a - floor(a/4.);
  }

  double bb = jd + b + 1524;
  double cc = floor((bb - 122.1) / 365.25);
  double dd = floor(365.25 * cc);
  double ee = floor((bb - dd) / 30.6001);
  tanggalH = (bb - dd) - floor(30.6001 * ee);
  bulanH = ee - 1;

  if(ee>13) {
    cc += 1;
    bulanH = ee-13;
  }
  tahunH = cc-4716;

  double iyear = 10631./30.;
  double epochastro = 1948084;
  double epochcivil = 1948085; //

  double shift1 = 8.01 / 60.;

  double z = jd-epochastro;

  double cyc = floor(z / 10631.);
  z = z - 10631 * cyc;
  double j = floor((z - shift1) / iyear);
  double iy = 30 * cyc + j;
  z = z - floor(j * iyear + shift1);
  double im = floor((z + 28.5001) / 29.5);
  
  if (im == 13){
    im = 12;
  }

  double id = z - floor(29.5001 * im - 29);

// Bulan Hijriyah
char MonthName[14];
memset(MonthName, 0, 14);
strcpy_P(MonthName, namaBulanHijriyah[int(im)-1]);

// Serial.print(int(im)-1);

//if (int(im)-1 == 2 /*Rabiul Awal*/ && int(id) == 12) 
//{
//  hari_besar = 1;
//} 
//else if (int(im)-1 == 9 /*Syawal*/ && int(id) == 1)
//{
//  hari_besar = 2;
//}
//else if (int(im)-1 == 11 /*Dzul Hijjah*/ && int(id) == 10)
//{
//  hari_besar = 3;
//}
//else if (int(im)-1 == 0 /*Muharram*/ && int(id) == 1)
//{
//  hari_besar = 5;
//}
//else if (int(im)-1 == 6 /*Rajab*/ && int(id) == 27)
//{
//  hari_besar = 6;
//}
//else // Hari biasa
//{
//  hari_besar = 4;
//}

//res_kalHij =  String(hari_besar) + String(int(id)) + " " + MonthName + " " + String(int(iy)) + " H";
res_kalHij =  String(int(id)) + " " + MonthName + " " + String(int(iy)) + " H";


return res_kalHij;
  
}
