var
    canv    = document.getElementById('canvas'),
    ctx     = canv.getContext('2d');

	canv.width  = window.innerWidth;
	canv.height = window.innerHeight;

var
	g = 9.8,
	speed = 0.1,
	w = 3,
	a = 70,
	r = 100,
	time = 0,
	start = 0,
	t = 10;				//framerate

var
	object = {
		r : 10,
		a : 80,
		g : 0.003,
		w : 0,
		l : 100,
		f : 0,
		x : 0,
		y : 0,
		angle : 0,
		v : 0
	},

	project = {
		F : 0,
		m : 0,
		phi : 0,
		a : 0,
		alpha : 0,
		N : 0,
		delta : 0.45,
		chart : {
			x : canv.width * 3 / 5,
			y : canv.height * 2 / 5,
			track : []
		},
		camera : {
			x : canv.width/7,
			y : canv.height/2
		},
		frames : -1,
		rectangle : {
			w : 80,
			h : 80
		}
	}

	camera = {
		x : canv.width/7,
		y : canv.height - 2*r
	},

	track = [],

	chart_xt = {
		x : canv.width*3/4,
		y : canv.height/3,
		track : []
	}

setInterval(function () {

	//update
	canv.width  = window.innerWidth;
	canv.height = window.innerHeight;

	///update cams
	project.camera.x = canv.width/7;
	project.camera.y = canv.height/2;

	project.chart.x = canv.width*3/5;
	project.chart.y = canv.height*2/5;

	///update values
	project.F = document.getElementById("constantf").value;
	project.m = document.getElementById("constantm").value;
	project.phi = document.getElementById("constantphi").value;
	project.alpha += project.delta;
	if (project.alpha > 89.8 && project.delta > 0) {
		project.delta *= -1;
	}
	if (project.alpha < 0.2 && project.delta < 0) {
		project.delta *= -1;
	}
	project.N = project.m * g - project.F * Math.sin(project.alpha * Math.PI / 180);
	if (project.N < 0) {
		project.N = 0;
	}
	project.a = (project.F * Math.cos(project.alpha * Math.PI / 180) - project.N * project.phi) / project.m;
	project.frames += 1;

	///update track
	console.log('m : ', project.m);
	console.log('F : ', project.F);
	console.log('phi : ', project.phi);
	console.log('alpha : ', project.alpha);
	console.log('N : ', project.N);
	console.log('a: ', project.a);
	project.chart.track.push({
		title : -123,
		a : project.a
	});
	if (!(project.frames % 100) || project.frames == 1) {
		project.chart.track[project.chart.track.length - 1].title = Math.round(project.alpha);
	}
	while (project.chart.track.length > 300) {
		project.chart.track.splice(0, 1);
	}

	

	///draw graph
	ctx.translate(project.camera.x, project.camera.y);
	///draw cube
	ctx.fillStyle = "#000";
	ctx.rect(-project.rectangle.w / 2, -project.rectangle.h / 2, 
		project.rectangle.w, project.rectangle.h);
	ctx.fill();
	///draw mg arrow
	ctx.lineWidth = 3;
	ctx.font = "20px Arial";
	ctx.fillStyle = "#00f";
	ctx.strokeStyle = "#00b";
	ctx.beginPath();
	ctx.moveTo(0, 0);
	ctx.lineTo(0, project.m * g);
	ctx.moveTo(0, project.m * g + 3);
	ctx.lineTo(7, project.m * g - 7);
	ctx.moveTo(0, project.m * g + 3);
	ctx.lineTo(-7, project.m * g - 7);
	ctx.fillText("mg", 0, project.m * g + 20);
	ctx.stroke();
	///draw N arrow
	if (project.N > 0) {
		ctx.beginPath();
		ctx.moveTo(0, 0);
		ctx.lineTo(0, -project.N);
		ctx.moveTo(0, -project.N - 3);
		ctx.lineTo(7, -project.N + 7);
		ctx.moveTo(0, -project.N - 3);
		ctx.lineTo(-7, -project.N + 7);
		ctx.fillText("N", 0, -project.N - 20);
		ctx.stroke();
	}
	///draw F arrow
	ctx.beginPath();
	ctx.moveTo(0, 0);
	ctx.lineTo(Math.cos(project.alpha * Math.PI / 180) * project.F, -Math.sin(project.alpha * Math.PI / 180) * project.F);
	
	ctx.moveTo(Math.cos(project.alpha * Math.PI / 180) * project.F + 3 * Math.cos(project.alpha * Math.PI / 180),
				-Math.sin(project.alpha * Math.PI / 180) * project.F - 3 * Math.sin(project.alpha * Math.PI / 180));
	
	ctx.lineTo(Math.cos(project.alpha * Math.PI / 180) * project.F - 12 * Math.sin((project.alpha + 60) * Math.PI / 180),
				-Math.sin(project.alpha * Math.PI / 180) * project.F - 12 * Math.cos((project.alpha + 60) * Math.PI / 180));

	ctx.moveTo(Math.cos(project.alpha * Math.PI / 180) * project.F + 3 * Math.cos(project.alpha * Math.PI / 180),
				-Math.sin(project.alpha * Math.PI / 180) * project.F - 3 * Math.sin(project.alpha * Math.PI / 180));

	ctx.lineTo(Math.cos(project.alpha * Math.PI / 180) * project.F - 12 * Math.cos((project.alpha + 30) * Math.PI / 180),
				-Math.sin(project.alpha * Math.PI / 180) * project.F + 12 * Math.sin((project.alpha + 30) * Math.PI / 180));

	ctx.fillText("F", Math.cos(project.alpha * Math.PI / 180) * project.F, -Math.sin(project.alpha * Math.PI / 180) * project.F);
	ctx.stroke();
	///draw F friction arrow
	if (project.N > 0) {
		ctx.beginPath();
		ctx.moveTo(-project.rectangle.w / 2, project.rectangle.h / 2);
		ctx.lineTo(-project.rectangle.w / 2 - project.N * project.phi, project.rectangle.h / 2);
		ctx.moveTo(-project.rectangle.w / 2 - project.N * project.phi - 3, project.rectangle.h / 2);
		ctx.lineTo(-project.rectangle.w / 2 - project.N * project.phi + 7, project.rectangle.h / 2 - 7);
		ctx.moveTo(-project.rectangle.w / 2 - project.N * project.phi - 3, project.rectangle.h / 2);
		ctx.lineTo(-project.rectangle.w / 2 - project.N * project.phi + 7, project.rectangle.h / 2 + 7);
		ctx.fillText("F friction", -project.rectangle.w / 2 - project.N * project.phi, project.rectangle.h / 2 + 20);
		ctx.stroke();
	}
	///draw alpha angle
	ctx.strokeStyle = "#0a0";
	ctx.beginPath();
	if (project.alpha > 0.5) {
		ctx.arc(0, 0, 20, 0, -project.alpha * Math.PI / 180, 1);
	}
	ctx.fillStyle = "#0a0";
	ctx.fillText(Math.round(project.alpha * 100) / 100, 20, -20);
	ctx.stroke();

	///graph done
	ctx.translate(-project.camera.x, -project.camera.y);


	///draw chart a(alpha)
	ctx.translate(project.chart.x, project.chart.y);
	///draw axises (MAGICK NUMBERS ALERT)
	ctx.lineWidth = 3;
	ctx.strokeStyle = "#000";
	ctx.beginPath();
	///axis X
	ctx.moveTo(0, 0);
	ctx.lineTo(303, 0);
	///arrow on axis X
	ctx.moveTo(305, 0);
	ctx.lineTo(290, -7);
	ctx.moveTo(305, 0);
	ctx.lineTo(290, 7);
	///axis Y
	ctx.moveTo(0, 0);
	ctx.lineTo(0, -303);
	///arrow on axis Y
	ctx.moveTo(0,-305);
	ctx.lineTo(-7, -295);
	ctx.moveTo(0,-305);
	ctx.lineTo(7, -295);
	///axises done
	ctx.stroke();

	let maxa = -999999999;
	///draw track
	ctx.strokeStyle = "#0f0";
	ctx.font = "30px Arial";
	ctx.beginPath();
	ctx.moveTo(0, project.chart.track[0]);
	for (var i = 1; i < project.chart.track.length; i++) {
		ctx.lineTo(i, -project.chart.track[i].a * 20);
		maxa = Math.max(maxa, project.chart.track[i].a);
	}
	ctx.stroke();

	///draw little lines under text
	ctx.strokeStyle = 'rgba(255, 0, 0, 0.2)';
	ctx.fillStyle = "#b00";
	ctx.beginPath();
	for (var i = 1; i < project.chart.track.length; i++) {
		if (project.chart.track[i].title != -123) {
			ctx.moveTo(i, 15);
			ctx.lineTo(i, -project.chart.track[i].a * 20 + 2);
			ctx.fillText(project.chart.track[i].title, i, 30);
		}
	}
	ctx.stroke();

	///type cur a
	ctx.fillStyle = "#222";
	ctx.fillText(Math.round(project.chart.track[project.chart.track.length - 1].a * 100) / 100, 
		project.chart.track.length + 15, 
		-project.chart.track[project.chart.track.length - 1].a * 20);
	ctx.stroke();

	//type max a
	ctx.fillStyle = "#555";
	ctx.fillText(Math.round(maxa * 100) / 100, 
		-40, 
		-maxa * 20);
	ctx.stroke();


	///chart done
	ctx.translate(-project.chart.x, -project.chart.y);

}, t);


function getRandomArbitrary(min, max) {
 	return Math.random() * (max - min) + min;
}