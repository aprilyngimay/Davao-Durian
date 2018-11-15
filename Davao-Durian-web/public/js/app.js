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