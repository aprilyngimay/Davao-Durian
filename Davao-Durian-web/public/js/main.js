$(function(){
	$.ajax({
		type:'GET',
		url:'https://api-uat.unionbankph.com/partners/sb/sandbox/v1/accounts',
		success: function(data){
			console.log('success', data);
		}
	});
});