uses Math;
label fin;
type     edge = record
            x1,y1,x2,y2 : double;
            A,B,C, len,Ap,Bp, Cp, dst, dmin : double;
            alfa_st, alfa_dr,uoxd, uoxs : double;
            l_st, l_dr : double;
            area_st, area_dr : double;
            intersect : integer;
            
            end;
            
      polygone = array[1..2000] of edge;
     
const
  delta = 0.0000001;      
var 
      p : polygone;
      j,count_st, count_dr,n, i, edgeC, edgeN, indexstang, indexdrept : integer;
      muchie1, muchie2, nodstart,l : integer;
      dimin, det,alfa,area, sposX, sposY, len, lenC : double;
      l1,l2,l3,ac,zid_dr_x, zid_dr_y, zid_st_x, zid_st_y : double;
      f,q: string;
      g : text;
procedure cleanmemory();
var i: integer;
begin 
     for i:=1 to 1000 do
      begin
        p[i].x1:=0; p[i].y1:=0; p[i].x2:=0; p[i].y2:=0;
            p[i].A :=0; p[i].B :=0; p[i].C := 0; p[i].len:=0; p[i].Ap :=0; p[i].Bp:=0; p[i].Cp:=0; p[i].dst:=0; p[i].dmin :=0;
            p[i].alfa_st:=0; p[i].alfa_dr:=0;
            p[i].l_st :=0; p[i].l_dr :=0;
            p[i].area_st:=0; p[i].area_dr := 0;
            p[i].intersect :=0;
      end;     
     
      j:=0;count_st:=0; count_dr:=0;n:=0; i:=0; edgeC:=0; edgeN:=0; indexstang:=0; indexdrept :=0;
      muchie1:=0; muchie2:=0; nodstart:=0;
      dimin:=0; det:=0;alfa:=0;area:=0; sposX:=0; sposY:=0; len:=0; lenC:=0;
      l1:=0;l2:=0;l3:=0;ac:=0;zid_dr_x:=0; zid_dr_y:=0; zid_st_x:=0; zid_st_y:=0;
 
end;     
       
function next_edge(i : integer; d: char) : integer;
 begin
  case d of
   'r' :  if i<n then next_edge := i+1 else next_edge := 1;
   'l' :  if i>1 then next_edge := i-1 else next_edge := n;
  end;
end;  

function distance (x1,y1,x2,y2: double ): double;
 begin
  distance := sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
 end; 
 
function sarrus(x1,y1,z1,x2,y2,z2,x3,y3,z3:double ): double;
  begin sarrus:= x1 * y2 * z3 + x2 * y3 * z1 + y1 * x3 * z2
               - x3 * y2 * z1 - x1 * z2 * y3 - x2 * y1 * z3;
  end; 
  
function unghi_Ox (x1,y1,x2,y2 : double) : double;
begin
 if (y1 = y2) and (x1 <x2) then unghi_Ox := 0 ;  
 if (y1 = y2) and (x1 > x2) then unghi_Ox := pi ;   
 if (x1 = x2) and (y1 <y2) then unghi_Ox := pi / 2 ;   
 if (x1 = x2) and (y1 >y2) then unghi_Ox := 1.5 * pi ;   
 if (y1 < y2) and (x1 <x2) then unghi_Ox := arcsin((y2 - y1)/ distance(x1,y1,x2,y2)) ;   
 if (y1 < y2) and (x1 > x2) then unghi_Ox := pi - arcsin((y2 - y1)/ distance(x1,y1,x2,y2)) ;   
 if (y1 > y2) and (x1 <x2) then unghi_Ox := 2*pi - arcsin((y1 - y2)/ distance(x1,y1,x2,y2)) ;   
 if (y1 > y2) and (x1 >x2) then unghi_Ox := pi + arcsin((y1 - y2)/ distance(x1,y1,x2,y2));
end; 

procedure arcsegment (q : integer; var xc ,yc : double);
var l1,l2,xa,xd,ya,yd,x,y : double;
begin
      // gasim unde exact se termina funia
      l1 := distance(p[q].x1,p[q].y1,sposX,sposY);
      l2 := distance(p[q].x2,p[q].y2,sposX,sposY);
      if l1 < l2 then begin xa := p[q].x1; ya := p[q].y1; xd := p[q].x2; yd := p[q].y2; end
               else begin xa := p[q].x2; ya := p[q].y2; xd := p[q].x1; yd := p[q].y1; end;
      // cautam binar           
      while distance(xa,ya,xd,yd) > delta do
        begin
         x := (xa + xd) / 2;
         y := (ya + yd) / 2;
        if distance(x,y,sposX,sposY) < len then begin  xa := x; ya:=y; end
                                           else begin  xd := x; yd:=y; end;
        end;
        
      xc :=x;   yc :=y; 
end;      
 
procedure readata(s : string);
var i: integer;
 d1,d2,d3, x_int, y_int : double;
begin
    nodstart :=0; dimin:=1000000000; 
{    assign(Input, s); reset(Input);}
    readln(sposX, sposY, len);
    readln(n);
    readln(p[1].x1, p[1].y1); 
    readln(p[1].x2, p[1].y2); 
    
    for i:=2 to n-1 do
     begin
      p[i].x1 := p[i-1].x2;
      p[i].y1 := p[i-1].y2;
      readln(p[i].x2, p[i].y2);
     end;
    p[n].x1 := p[n-1].x2;
    p[n].y1 := p[n-1].y2;
    p[n].x2 := p[1].x1;
    p[n].y2 := p[1].y1;
    close(Input);
    for i:=1 to n do
     begin
     // coeficienti
      p[i].A := p[i].y2 - p[i].y1;
      p[i].B := p[i].x1 - p[i].x2;
      p[i].C := p[i].x2*p[i].y1 - p[i].x1*p[i].y2;
      // lungimea muchiei
      p[i].len := distance(p[i].x1,p[i].y1,p[i].x2,p[i].y2);
      // coeficienti dreaptaa perpendiculare care trece prin centrul cerculi
      p[i].Ap := p[i].B;
      p[i].Bp := -p[i].A;
      p[i].Cp := p[i].A*sposY - p[i].B*sposX;
      // distantele de la capete la centrul cercului
      d1 := distance(p[i].x1,p[i].y1,sposX,sposY);
      d2 := distance(p[i].x2,p[i].y2,sposX,sposY);
      if d1 < dimin then begin nodstart := i; dimin := d1; end;
      
      // distantsa de la centrul cercului la dreapta - muchie
         if p[i].A <>0 then
         begin
          y_int := (p[i].A *p[i].Cp - p[i].B * p[i].C) / (p[i].A *p[i].A + p[i].B * p[i].B);
          x_int := -(p[i].B * y_int +P[i].C) / p[i].A;
         end
      else
         begin
          y_int := -p[i].C /  p[i].B;
          x_int := -p[i].Cp / p[i].B;
         end;  
      // intersectia razei cu muchia   
      
      d3 := distance(x_int,y_int,sposX,sposY);
    //  writeln(i, ' ', x_int:6:2, ' ',y_int:6:2,' ', d3 );   
      p[i].dst :=d3;
      if (d1>len) and (d2<len) or (d1<len) and (d2>len) then p[i].intersect :=1 else
      if (d1>len) and (d2>len) and (d3<len) and (abs(distance(p[i].x1,p[i].y1,x_int,y_int)+ distance(p[i].x2,p[i].y2,x_int,y_int) - p[i].len) < delta) then p[i].intersect :=2 else p[i].intersect :=0;
      if d1 <d2 then p[i].dmin := d1 else p[i].dmin := d2;
      p[i].uoxd :=unghi_Ox (p[i].x1, p[i].y1,p[i].x2, p[i].y2); 
      p[i].uoxs :=unghi_Ox (p[i].x2, p[i].y2,p[i].x1, p[i].y1); 
      
 end;
end;

      
function arietriunghi(x1,y1,x2,y2,x3,y3 : double) : double;
 begin 
     arietriunghi := abs(sarrus(x1,y1,1,x2,y2,1,x3,y3,1))/2;
 end;  
   
 
function sectorarea (angle, radius : double): double;
 begin
  sectorarea := radius*radius / 2 * angle;
 end; 
 
function find_angle (x1,y1,x2,y2,x3,y3 : double ) : double;
var a,b,c,p: double;
begin
   a:= distance(x1,y1,x2,y2); 
   b:= distance (x1, y1,x3, y3);
   c:= distance(x3,y3,x2,y2);
   p := (a+b+c) / 2;
 find_angle := pi-2*arcsin (sqrt((p-a)*(p-c)/a/c));
end; 

function AreaSpecial (z : edge) : double;
var a,b,c, uC,uB, p, s3,ssl, ssr : double;
begin
    a := z.len;
    b := z.l_dr;
    c := z.l_st;
    if b+c <=a then 
       begin
         AreaSpecial := z.area_st +z.area_dr;
         exit;
       end;  
    p := (a + b + c) / 2;
    uC := 2*arcsin (sqrt((p-a)*(p-b)/a/b));
    uB := 2*arcsin (sqrt((p-a)*(p-c)/a/c));
    s3 := sqrt(p*(p-a)*(p-b)*(p-c));
    ssl := sectorarea(z.alfa_st - uB, c);
    ssr := sectorarea(z.alfa_dr - uC, b);
    AreaSpecial := s3 + ssl + ssr;
end;    
  
function solve1(i :integer) : double;
var coardjum, alfa : double;  
 begin
  coardjum := sqrt(len*len - p[i].dst*p[i].dst);
  alfa := arcsin(coardjum / len); // de fapt asta e jumate din unchi
  // dar  se simplific[ formulele de calcul a ariei
  solve1 := len*len*(pi - alfa) + p[i].dst * coardjum;
 end;
 
  
 begin 

   f := 'tc.in';
    q:= 'ft.out';

  {assign (g, q); rewrite(g);}
    muchie1 :=0; muchie2 :=0;
    cleanmemory();  
    readata (f);
   
    for i:=1 to n do
     if (p[i].intersect <>0) and (muchie1 = 0) then muchie1 := i else 
     if (p[i].intersect <>0) and (muchie1 <> 0) then muchie2 := i;
   
 //  calcul arie subtask 1
 if (muchie1 = 0) and (dimin > len)  then 
    begin 
    write((pi*len*len):0:5);
     exit; 
     // goto fin;
    end 
   else  if (muchie1 <> 0) and (muchie2 = 0)  then 
    begin
    write(solve1(muchie1):0:5);
    {write(g, solve1(muchie1));}
    {close(g);}
   //  goto fin;
    exit;
    end; 
 
    // cel mai stang și cel mai drept varf (cele care vor genera indoituri a funiei)
   indexstang := 0; indexdrept:= 0;
   for i := 1 to n do
    begin 
       count_st := 0; count_dr := 0;
    for j:=1 to n do
     begin
      det := sposX*p[i].y1 + p[j].y1*p[i].x1 + p[j].x1*sposY - p[j].x1*p[i].y1 - p[i].x1*sposY - p[j].y1*sposX;
      if (j <> i) and (det > 0) then count_st :=1;
      if (j <> i) and (det < 0) then count_dr :=1;
     end;
   if count_st = 0 then indexstang := i;
   if count_dr = 0 then indexdrept := i;
   end; 

   // calculare arii
  edgeC := nodstart;
  area :=0;
  
  // mergem dupa acele de ceas - stanga
   while (p[edgeC].intersect =0) and (edgeC <> indexstang) do
  begin
    p[edgeC].area_dr:= arietriunghi(sposX, sposY, p[edgeC].x1, p[edgeC].y1, p[edgeC].x2, p[edgeC].y2);
    edgeC := next_edge(edgeC, 'r');
  end;
  // se termina frangia;
  
     if (p[edgeC].intersect =1) then // ultima linie 
           if (edgeC <> indexstang) then 
              begin
                 arcsegment (edgeC, zid_dr_x, zid_dr_y); // gasim punctul de intersec'ie
                if distance (sposX,sposY, p[edgeC].x2, p[edgeC].y2) < distance (sposX,sposY, p[edgeC].x1, p[edgeC].y1)
                 then  ac := arietriunghi(sposX, sposY, p[edgeC].x2, p[edgeC].y2, zid_dr_x, zid_dr_y)
                 else  ac := arietriunghi(sposX, sposY, p[edgeC].x1, p[edgeC].y1, zid_dr_x, zid_dr_y);
                 p[edgeC].area_dr:= ac;
              end
              else
              begin
               lenC := len - distance(p[edgeC].x1, p[edgeC].y1, sposX, sposY);
               p[edgeC].alfa_dr := find_angle(p[edgeC].x2,p[edgeC].y2,p[edgeC].x1,p[edgeC].y1, sposX,sposY );
               p[edgeC].area_dr:= sectorarea (p[edgeC].alfa_dr, lenC);
               p[edgeC].l_dr := lenC;
               zid_dr_x := p[edgeC].x1;  zid_dr_y := p[edgeC].y1;
               lenc := 0;
              end
           else // nu e ultima linie, dar se indoaie
             begin
             lenC := len - distance(p[edgeC].x1, p[edgeC].y1, sposX, sposY);
             zid_dr_x := p[edgeC].x1;  zid_dr_y := p[edgeC].y1;
               p[edgeC].alfa_dr := find_angle(p[edgeC].x2,p[edgeC].y2,p[edgeC].x1,p[edgeC].y1, sposX,sposY );
               p[edgeC].area_dr:= sectorarea (p[edgeC].alfa_dr, lenC);
               if lenc < p[edgeC].len then p[edgeC].l_dr := lenC;
               alfa := unghi_Ox (sposX,sposY,p[edgeC].x1,p[edgeC].y1 );
               lenc := lenc - p[edgec].len;
              while lenC > 0 do
               begin
                 edgeN := next_edge(edgeC,'r');
                 p[edgeN].alfa_dr := find_angle(p[edgeC].x1,p[edgeC].y1,p[edgeC].x2,p[edgeC].y2, p[edgeN].x2,p[edgeN].y2 );
                 p[edgeN].area_dr:= sectorarea (p[edgeN].alfa_dr, lenC);
                 if lenc < p[edgeN].len then p[edgeN].l_dr := lenC;
                 edgeC := edgeN;
                 if lenC > p[edgeN].len then lenC := lenC - p[edgeN].len else lenC :=0;
               end;  
             end;
    
// si mergem impotriva acelor   
  if nodstart <> 1 then edgeC := nodstart-1 else edgeC := n;
  lenC :=len;
  while (p[edgeC].intersect =0) and ( edgeC <> indexdrept-1) do
  begin
   p[edgeC].area_st:= arietriunghi(sposX, sposY, p[edgeC].x1, p[edgeC].y1, p[edgeC].x2, p[edgeC].y2);
   edgeC := next_edge(edgeC, 'l');
  end;
  
   // daca se termina funia
   if (p[edgeC].intersect =1)  then 
       if (edgeC <> indexdrept-1) then 
              begin// doar triunghi
                 arcsegment (edgeC, zid_st_x, zid_st_y); // gasim punctul de intersec'ie
                 if distance (sposX,sposY, p[edgeC].x2, p[edgeC].y2) < distance (sposX,sposY, p[edgeC].x1, p[edgeC].y1)
                 then  ac := arietriunghi(sposX, sposY, p[edgeC].x2, p[edgeC].y2, zid_st_x, zid_st_y)
                 else  ac := arietriunghi(sposX, sposY, p[edgeC].x1, p[edgeC].y1, zid_st_x, zid_st_y);
                 p[edgeC].area_st:= ac;
               end
          else  // daca se indoaie funia
            begin
              lenC := len - distance(p[edgeC].x2, p[edgeC].y2, sposX, sposY);
              zid_st_x := p[edgeC].x2;  zid_st_y := p[edgeC].y2;
              p[edgeC].alfa_st := find_angle(p[edgeC].x1,p[edgeC].y1,p[edgeC].x2,p[edgeC].y2, sposX,sposY );
              p[edgeC].area_st:= sectorarea (p[edgeC].alfa_st, lenC);
              if lenc < p[edgeC].len then p[edgeC].l_st := lenC;
              alfa := unghi_Ox (sposX,sposY,p[edgeC].x2,p[edgeC].y2 );
              lenc := 0;
           end
        else
          begin
          lenC := len - distance(p[edgeC].x2, p[edgeC].y2, sposX, sposY);
          zid_st_x := p[edgeC].x2;  zid_st_y := p[edgeC].y2;
          p[edgeC].alfa_st := find_angle(sposX,sposY,p[edgeC].x2,p[edgeC].y2,p[edgeC].x1,p[edgeC].y1  );
          p[edgeC].area_st:= sectorarea (p[edgeC].alfa_st, lenC);
          if lenc < p[edgeC].len then p[edgeC].l_st := lenC;
          alfa := unghi_Ox (sposX,sposY,p[edgeC].x2,p[edgeC].y2 );
          p[i].uoxs :=unghi_Ox (p[i].x2, p[i].y2,p[i].x1, p[i].y1); 
          lenc := lenc - p[edgec].len;
          while lenC > 0 do
           begin
            edgeN := next_edge(edgeC,'l');
            p[edgeN].alfa_st := find_angle(p[edgeC].x2,p[edgeC].y2,p[edgeC].x1,p[edgeC].y1, p[edgeN].x1,p[edgeN].y1 );
            p[edgeN].area_st:= sectorarea (p[edgeN].alfa_st, lenC);
            if lenc < p[edgeN].len then p[edgeN].l_st := lenC;
            edgeC := edgeN;
            if lenC > p[edgeN].len then lenC := lenC - p[edgeN].len else lenC :=0;
          end;  
        end; 
      
   //aria diggerului
  
   l1:= distance(zid_dr_x,zid_dr_y,zid_st_x, zid_st_y);
   l2 := distance(zid_dr_x,zid_dr_y,sposX,sposY);
   l3 := distance(zid_st_x,zid_st_y,sposX,sposY);
   alfa := arccos( (l2*l2 +l3*l3 - l1*l1)/( 2*l2*l3));
 
   area := len*len*(pi - alfa/2);
 
   for i:=1 to n do
    if (p[i].area_st >0 ) and (p[i].area_dr =0 ) or (p[i].area_dr >0 ) and (p[i].area_st =0 )
    then area := area + p[i].area_st + p[i].area_dr
    else if (p[i].area_st >0 ) and (p[i].area_dr > 0 )then begin area := area+ AreaSpecial(p[i]); end;
    write(area:0:5);
{    write(g, area);
  close(g);}
    
 
end.   
   
