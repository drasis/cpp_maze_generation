var rows, columns;
var boxSize, buttWidth;
var inp, saveButton, mycanv;
var grid = [];
var solution;
var valid = false;
var path = [];
var showSolution = false;
var inpDefault = "395513d139539551555555395513b9155393d1393d15553d13\n\
c453ac56aabae9569539796e93ac6ac5386c56c6a96953c56a\n\
953ec397aac296956d4696916aa93ab92e9393d3aabc3a9556\n\
c3a956a9683aa9695553abaabc2ac6aae96c6c3ac683ac6953\n\
96c6916c3eac6c3c393c6aaaa96a952a94795568552ead387a\n\
c5396a95456953c3c6ad16aac43c696ac396d396d3c3c3c692\n\
95683e85793aba9293c3c56853e93a907ac53aa952969693aa\n\
ad56c56956aac46ae87a953abc52c6ae9457aaaa96c5692aaa\n\
a9539556b968393c3a96a96c693c57c3c3956846c5397aac6a\n\
c696a9556abac6c3c6a96a9556a9395296ad569553a83ac3ba\n\
93a96a9556a87938556a96ad13aac696a96955457aaec2bac6\n\
aaaad2c3d54696aa9516c3c3ae869387ac56d1393ac53c2c53\n\
ac2c3c3c5553a96c6d693c56a9696ae9455556aac6956d2b96\n\
ad43c52d153c6c553956a953c296bc56b953d56c3bad13c6c3\n\
853ad3c56bc393d3c697c6bc3ac3a9512ad455556ac56c553a\n\
a96a94553856ac3855413d03aaba8696ac53d5553839395542\n\
ac3c69556a956bac7952c56eaaaac3abc39695392ac6aa93d6\n\
a96d54793aa954693aba93956c6abaac56a96946ea952aac53\n\
ac539556c46a953ac686ac695556aaa953aad6953aad6ac3d2\n\
c53aa955393c696853c7a956939786c696aa93abaac5547c3a\n\
d52c6c3bc6c3bc387c53c6d52ac54793c3ac6aaac45579556a\n\
93c5396a955683aa95145393ac55556c3ac53868395556953a\n\
aa93ec3c4397aaaec3e93c2c6955395568796ad2aab939692a\n\
ac6c53c3bac56ac55296ad695693aa953c3abc3aaaaac696ea\n\
c3939696ac55387956abc55693aaac2d456ac16eaa8693c396\n\
96eaa9690795685479685557ac6aaba955383a952aa96a96c3\n\
a93aaabac5693e9556969539697c686ad3aaaaabaeac3c6956\n\
86aaaaac3d16c3a95545692a9295547c386eac6c4387a95697\n\
c3aa86c52969546e95553aeae86955396c3969553ea96a9543\n\
96ac6953c6d47953ab956c3c3c7c3bc6d3a83ad3c56c56c53a\n\
a96956bc395556bc6aa95547c3956c1552aeac3c155553b96a\n\
ac5695296c3d538552ac39553ac3956d16c383c5695796aaba\n\
c53d296a93a956c392c3c457c456c393e956ae955453a9446a\n\
93c56c3aaaac5516ac7c395555393c6c5453a96b9156ae9392\n\
a857956c6ac553abc517c6d513aac5551396c056ae93a96c6a\n\
ac556913bc517ac457c155396aaa9553eaa93e95296c6c393a\n\
ad153eaa853c3c55553ad3aa96c6ab9692c6c56d6c3953c6aa\n\
c3c3c56aabc3c39553c696c6a9792c456e955539556abc396a\n\
bc3c553aaa9696c5387929396a96e95553ad53aa939683c6ba\n\
c545556c6c47c5556c56c6c456c554557c4556c46c456c556c"

function setup() {
  mycanv = createCanvas(windowHeight, windowHeight);
  mycanv.position(windowWidth - windowHeight, 0);
  textAlign(CENTER, CENTER);

  initDOM();

  valid = true;
  grid = inpDefault.split("\n");
  rows = grid.length;
  columns = grid[0].length;
  for (var i = 0; i < rows; i++) {
    if (grid[i].length != columns) {
      valid = false;
      break;
    }
  }
  if ((grid.length === 1 && grid[0] == "") || columns == 0) {
    valid = false;
  }
  boxSize = (height * .9)/max(rows, columns);
  bfs();
}

function initDOM() {
  inp = createElement('textarea');
  inp.style('width', str(windowWidth - windowHeight - 20) + 'px');
  inp.position(10, inp.position.y);
  inp.input(handleInput);
  inp.value(inpDefault);

  buttWidth = (windowWidth - windowHeight - 20)/2;
  showSolutionButton = createButton('SHOW SOLUTION');
  showSolutionButton.class('buttStyle');
  showSolutionButton.style('width', str(buttWidth - 5) + 'px');
  showSolutionButton.position(buttWidth + 15, 375);
  showSolutionButton.mousePressed(toggleSolution);
  saveButton = createButton('SAVE');
  saveButton.class('buttStyle');
  saveButton.style('width', str(buttWidth - 5) + 'px');
  saveButton.position(10, 375);
  saveButton.mousePressed(saveMaze);
}

function handleInput() {
  valid = true;
  grid = this.value().split("\n");
  rows = grid.length;
  columns = grid[0].length;
  for (var i = 0; i < rows; i++) {
    if (grid[i].length != columns) {
      valid = false;
      break;
    }
  }
  if ((grid.length === 1 && grid[0] == "") || columns == 0) {
    valid = false;
  }
  boxSize = (height * .9)/max(rows, columns);
  bfs();
  draw();
}

function saveMaze() {
  saveCanvas(mycanv, 'maze', 'png');
}

function toggleSolution() {
  showSolution = !showSolution;
  if (!showSolution) {
    this.elt.textContent = "SHOW SOLUTION";
  } else {
    this.elt.textContent = "HIDE SOLUTION";
  }
  draw();
}

function lerpColors(colors, val) {
  if (colors.length == 1) {
    return color(colors[0]);
  }
  if (colors.length == 2) {
    return lerpColor(color(colors[0]), color(colors[1]), val);
  }
  var v = int(val * (colors.length - 1));
  var newval = (colors.length - 1) * val - v;
  return lerpColor(color(colors[v]), color(colors[v + 1]), newval);
}

function draw() {
  background("white");
  if (!valid) {
    text("waiting for valid input", width/2, height/2);
    noLoop();
  } else {
    push();
    translate(height * .05 + max(0, boxSize/2 * (rows - columns)), 
      height * .05 + max(0, boxSize/2 * (columns - rows)));

    noStroke();
    strokeWeight(1);
    if (showSolution) {
      for (var i = 0; i < path.length; i++) {
        fill(lerpColors(["red", "orange","yellow", "springgreen","dodgerblue","mediumpurple"], i/path.length));
        stroke(lerpColors(["red", "orange","yellow", "springgreen","dodgerblue","mediumpurple"], i/path.length));
        rect(path[i].c * boxSize, path[i].r * boxSize, boxSize, boxSize);
      }   
    }

    fill("white");
    for (var r = 0; r < rows; r++) {
      for (var c = 0; c < columns; c++) {
        if (true) {}
      }
    }

    stroke("black");
    strokeWeight(2);
    for (var r = 0; r < rows; r++) {
      for (var c = 0; c < columns; c++) {
        push();
        translate(c * boxSize, r * boxSize);
        var bits = getBits(grid[r][c]);
        if (bits[0]) {
          line(0, 0, boxSize, 0);
        }
        if (bits[1]) {
          line(boxSize, 0, boxSize, boxSize);
        }
        if (bits[2]) {
          line(boxSize, boxSize, 0, boxSize);
        }
        if (bits[3]) {
          line(0, boxSize, 0, 0)
        }
        pop();
      }
    }
    pop();
    if (!valid) {
      redraw(1);
    } else {
      noLoop();
    }
  }
  // console.log("drawing" + str(frameCount))
}


function getBits(n) {
  var vals = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, 
  '6': 6, '7': 7, '8': 8, '9': 9, 'a': 10, 'b': 11, 'c': 12, 
  'd': 13, 'e': 14, 'f': 15};
  if (!(n in vals)) {
    valid = false;
  }
  var val = vals[n];
  var ret = [];
  for (var j = 0; j < 4; j++) {
    ret.push(floor(val/2) != val/2);
    val = floor(val/2);
  }
  return ret;
}

function windowResized() {
  resizeCanvas(windowHeight, windowHeight);
  inp.style('width', str(windowWidth - height - 20) + 'px');
  mycanv.position(windowWidth - height, 0);
  buttWidth = (windowWidth - windowHeight - 20)/2;
  showSolutionButton.style('width', str(buttWidth - 5) + 'px');
  showSolutionButton.position(buttWidth + 15, 375);
  saveButton.style('width', str(buttWidth - 5) + 'px');
  saveButton.position(10, 375);
  boxSize = (windowHeight * .9)/max(rows, columns);
  draw();
}
