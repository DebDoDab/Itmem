var
    canv    = document.getElementById('canvas'),
    ctx     = canv.getContext('2d');

	canv.width  = window.innerWidth;
	canv.height = window.innerHeight;

var
	t = 10;				//framerate

var
  // y = y0 * cos(wy*t + delta_y), x = x0 * cos(wx*t)
  y0 = 0,
  wy = 0,
  delta_y = 0,
  x0 = 0,
  wx = 0,
  frames = 0,
  x = 0,
  y = 0,

	track = []

setInterval(function () {

	//update
	canv.width  = window.innerWidth;
	canv.height = window.innerHeight;

	///update values
  frames += 1;
	let new_y0 = Number(document.getElementById("constanty0").value);
	let new_x0 = Number(document.getElementById("constantx0").value);
	let new_wy = Number(document.getElementById("constantwy").value);
	let new_wx = Number(document.getElementById("constantwx").value);
	let new_delta_y = Number(document.getElementById("constantdeltay").value) * Math.PI;
  if (new_wx != wx || new_x0 != x0 || new_y0 != y0 || new_delta_y != delta_y || new_wy != wy) {
    track = [];
    wx = new_wx;
    wy = new_wy;
    x0 = new_x0;
    y0 = new_y0;
    delta_y = new_delta_y;
    frames = 0;
  }
  x = calcx();
  y = calcy();
  let side = Math.min(canv.height / 4, canv.width / 4)

  let coeff = side / 5
	///update track
  track.push([x, y])


	///draw screen
	ctx.translate(canv.width / 2, canv.height / 2);


  //draw frame
  ctx.fillStyle = "#000";
  ctx.beginPath();
  ctx.moveTo(-side, -side);
  ctx.lineTo(side, -side);
  ctx.lineTo(side, side);
  ctx.lineTo(-side, side);
  ctx.lineTo(-side, -side);
  ctx.stroke();

  //draw axis
  ctx.lineWidth = 3;
  ctx.font = "20px Arial";
  ctx.fillStyle = "#00f";
  ctx.strokeStyle = "#00b";
  ctx.beginPath();
  ctx.moveTo(-side, 0);
  ctx.lineTo(side, 0);
  ctx.moveTo(0, -side);
  ctx.lineTo(0, side);
  ctx.stroke();





	///draw track
	ctx.strokeStyle = "#0f0";
	ctx.beginPath();
	ctx.moveTo(track[0][0] * coeff, -track[0][1] * coeff);
	for (var i = 1; i < track.length; i++) {
		ctx.lineTo(track[i][0] * coeff,- track[i][1] * coeff);
	}
	ctx.stroke();

  //red dot as current position
  ctx.beginPath();
  ctx.strokeStyle = "#f00";
  ctx.arc(track[track.length - 1][0] * coeff, -track[track.length - 1][1] * coeff, 5, 0, 2 * Math.PI);
  ctx.stroke();


  ///all done
  ctx.translate(-canv.width / 2, canv.height / 2);

}, t);


function calcx() {
  let x = x0 * Math.cos(wx * t * frames / 1000);
  return x
}

function calcy() {
 	let y = y0 * Math.cos(wy * t * frames / 1000 + delta_y);
  return y
}
