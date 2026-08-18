// vibe-EPD reference enclosure v0.1
// Reference display: Good Display GDEY042T81, 91 x 77 x 1.2 mm
// Reference PCB: EPD_S3_Universal v0.15, 60 x 45 mm, M3 holes 3.5 mm from corners
// Fit-check prototype, not a certified production enclosure.

$fn = 48;
part = "assembly"; // "front", "back", "assembly"

outer_w = 104;
outer_h = 90;
corner_r = 5;
wall = 2.0;
front_t = 3.0;
back_depth = 13.0;
screen_w = 91.0;
screen_h = 77.0;
window_w = 86.0;
window_h = 65.0;
pcb_w = 60.0;
pcb_h = 45.0;
pcb_x = (outer_w-pcb_w)/2;
pcb_y = (outer_h-pcb_h)/2;
boss_h = 6.0;
boss_od = 6.4;
boss_hole = 2.8;

module rounded2d(w,h,r){ hull(){ for(x=[r,w-r], y=[r,h-r]) translate([x,y]) circle(r=r); } }

module front_frame(){
  difference(){
    linear_extrude(front_t) rounded2d(outer_w,outer_h,corner_r);
    translate([(outer_w-window_w)/2,(outer_h-window_h)/2,-0.1]) cube([window_w,window_h,front_t+0.2]);
    translate([outer_w/2-8,0,-0.1]) cube([16,4,front_t+0.2]);
  }
  translate([(outer_w-screen_w)/2,(outer_h-screen_h)/2,front_t]) difference(){
    linear_extrude(0.8) square([screen_w,screen_h]);
    translate([1.2,1.2,-0.1]) linear_extrude(1.0) square([screen_w-2.4,screen_h-2.4]);
  }
}

module boss(x,y){ difference(){ translate([x,y,wall]) cylinder(h=boss_h,d=boss_od); translate([x,y,wall-0.1]) cylinder(h=boss_h+0.2,d=boss_hole); } }

module back_shell(){
  difference(){
    linear_extrude(back_depth) rounded2d(outer_w,outer_h,corner_r);
    translate([wall,wall,wall]) linear_extrude(back_depth) rounded2d(outer_w-2*wall,outer_h-2*wall,max(corner_r-wall,1));
    translate([-0.1, pcb_y+15, 4.0]) cube([wall+1.0,15,7]);
    translate([outer_w-0.1, pcb_y+10, 4.5]) cube([wall+1.0,25,4]);
    translate([outer_w/2,outer_h-8,-0.1]) cylinder(h=wall+0.2,d=5.5);
    translate([outer_w/2-1.5,outer_h-8,-0.1]) cube([3,6,wall+0.2]);
  }
  for(px=[3.5,56.5], py=[3.5,41.5]) boss(pcb_x+px, pcb_y+py);
  translate([8,12,wall]) cube([4,66,3]);
  translate([outer_w-12,12,wall]) cube([4,66,3]);
}

if(part=="front") front_frame();
if(part=="back") back_shell();
if(part=="assembly"){
  color("#ded7c8") front_frame();
  color("#34363a") translate([0,0,front_t+0.8]) back_shell();
}
