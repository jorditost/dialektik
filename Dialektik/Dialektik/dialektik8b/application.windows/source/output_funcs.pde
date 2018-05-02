//import krister.Ess.*;

public void change() {

  if (state) {
    fill(255);
    ellipse (300,300,400,400);
    fill(0);
    rect (285,50,30,500);   

    mySoundA.play(1);
    state = false;
  }
  else {
    fill(255);
    rect (285,50,30,550);  
    fill(0);
    ellipse (300,300,400,400);
    fill(255);
    ellipse (300,300,340,340);

    mySoundB.play(1);
    state = true;
  }

}



