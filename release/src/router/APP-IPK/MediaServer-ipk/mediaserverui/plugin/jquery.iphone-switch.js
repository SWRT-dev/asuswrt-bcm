jQuery.fn.iphoneSwitch = function(start_state, switched_on_callback, switched_off_callback, options) {

	var state = start_state == '1' ? start_state : '0';
	
	// define default settings
	var settings = {
		mouse_over: 'pointer',
		mouse_out:  'default',
		switch_on_container_path: 'plugin/iphone_switch_container_on.png',
		switch_off_container_path: 'plugin/iphone_switch_container_off.png',
		switch_path: 'plugin/iphone_switch.png',
		switch_height: 32,
		switch_width: 74
	};

	if(options) {
		jQuery.extend(settings, options);
	}

	// create the switch
	return this.each(function() {

		var container;
		var image;
		
		// make the container
		container = '<div class="iphone_switch_container" style="height:'+settings.switch_height+'px; width:'+settings.switch_width+'px; position: relative; overflow: hidden">';
		
		// make the switch image based on starting state
		image = '<img class="iphone_switch" src="'+(state == '1' ? settings.switch_on_container_path : settings.switch_off_container_path)+'" style="height:'+settings.switch_height+'px; width:'+settings.switch_width+'px; background-image:url('+settings.switch_path+'); background-repeat:none; background-position:'+(state == '1' ? 0 : -37)+'px" /></div>';

		// insert into placeholder
		jQuery(this).html(container + image);

		jQuery(this).mouseover(function(){
			jQuery(this).css("cursor", settings.mouse_over);
		});

		jQuery(this).mouseout(function(){
			jQuery(this).css("background", settings.mouse_out);
		});

		// click handling
		jQuery(this).click(function() {
			if(state == '1') {
				jQuery(this).find('.iphone_switch').animate({backgroundPosition: -37}, "slow", function() {
					jQuery(this).attr('src', settings.switch_off_container_path);
					switched_off_callback();
				});
				state = '0';
			}
			else {
				jQuery(this).find('.iphone_switch').animate({backgroundPosition: 0}, "slow", function() {
					switched_on_callback();
				});
				jQuery(this).find('.iphone_switch').attr('src', settings.switch_on_container_path);
				state = '1';
			}
		});		

	});
	
};
