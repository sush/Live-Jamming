$(document).ready(function(){
	$('.play').click(function(){
		var dewp = document.getElementById("dewplayer");
		if(dewp!=null) {
		    dewp.dewset('/files/jamsession/'+$(this).attr('value'));
		}
	    });
    });