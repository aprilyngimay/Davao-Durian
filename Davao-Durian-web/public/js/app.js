const urlwl = 'https://u-hackademia-davao-durian.firebaseio.com/arduinoDevice/waterLevel.json'
const wl = fetch(urlwl).then(res => res.json()).then(json => {return JSON.stringify(json)});


$(document).ready(function(){
	var database = firebase.database();
	var Switch;

	database.ref('/arduinoDevice/').on('value', function(snap){
		Switch = snap.val().Switch;
		if(Switch == 1){
			$(".status").text("AUTO");
		} else {
			$(".status").text("OFF");
		}
	});

	$(".sWitch").click(function(){
		var firebaseRef = firebase.database().ref('/arduinoDevice/Switch');

		if(Switch == 1){
			firebaseRef.set(0);
			Switch = 0;
		} else {
			firebaseRef.set(1);
			Switch = 1;
		}
	});
});

$(document).ready(function(){
	var database = firebase.database();
	var waterLevel;
	database.ref('/arduinoDevice/').on('value' , function(snap){
		waterLevel = snap.val().waterLevel;

		if (waterLevel == 1) {
			$(".water-status").text("LOW");
		} else if (waterLevel == 3) {
			$(".water-status").text("HIGH");
		} else {
			$(".water-status").text("NORMAL");
		}
	});
});