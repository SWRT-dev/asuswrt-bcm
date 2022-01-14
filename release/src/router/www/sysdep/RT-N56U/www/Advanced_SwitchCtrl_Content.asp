﻿<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<html xmlns:v>
<head>
<meta http-equiv="X-UA-Compatible" content="IE=Edge"/>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta HTTP-EQUIV="Pragma" CONTENT="no-cache">
<meta HTTP-EQUIV="Expires" CONTENT="-1">
<link rel="shortcut icon" href="images/favicon.png">
<link rel="icon" href="images/favicon.png">
<title><#Web_Title#> - <#Switch_itemname#></title>
<link rel="stylesheet" type="text/css" href="index_style.css"> 
<link rel="stylesheet" type="text/css" href="form_style.css">
<link rel="stylesheet" type="text/css" href="other.css">
<script type="text/javascript" src="/state.js"></script>
<script type="text/javascript" src="/general.js"></script>
<script type="text/javascript" src="/popup.js"></script>
<script type="text/javascript" src="/help.js"></script>
<script type="text/javascript" src="/validator.js"></script>

<script>

function initial(){
	var nataccel = '<% nvram_get("hwnat"); %>';
	var nataccel_status = '<% nat_accel_status(); %>';

	if(nataccel == '1' && nataccel_status == '1'){
		document.getElementById("natAccelDesc").innerHTML = "<#NAT_Acceleration_enable#>";
	}
	else{
		document.getElementById("natAccelDesc").innerHTML = "<#NAT_Acceleration_ctf_disable#>";
	}
	show_menu();
	if(based_modelid == "RT-N14U" || based_modelid == "RT-N11P" || based_modelid == "RT-N300" ||
	   based_modelid == "RT-AC52U" || based_modelid == "RT-AC51U" || based_modelid == "RT-N54U")
	{
		inputCtrl(document.form.switch_ctrlrate_unknown_unicast, 0);
		inputCtrl(document.form.switch_ctrlrate_unknown_multicast, 0);
		inputCtrl(document.form.switch_ctrlrate_multicast, 0);
		inputCtrl(document.form.switch_ctrlrate_broadcast, 0);
	}
}

function applyRule(){
		if(valid_form()){
				showLoading();
				document.form.submit();	
		}
}

function valid_form(){
	if(!validator.range(document.form.switch_ctrlrate_unknown_unicast, 0, 1024) ||
	   !validator.range(document.form.switch_ctrlrate_unknown_multicast, 0, 1024) ||
	   !validator.range(document.form.switch_ctrlrate_multicast, 0, 1024) ||
	   !validator.range(document.form.switch_ctrlrate_broadcast, 0, 1024)){
			return false;
	}

	return true;
}

</script>
</head>

<body onload="initial();" onunLoad="return unload_body();">
<div id="TopBanner"></div>
<div id="hiddenMask" class="popup_bg">
	<table cellpadding="5" cellspacing="0" id="dr_sweet_advise" class="dr_sweet_advise" align="center">
		<tr>
		<td>
			<div class="drword" id="drword" style="height:110px;"><#Main_alert_proceeding_desc4#> <#Main_alert_proceeding_desc1#>...
				<br/>
				<br/>
	    </div>
		  <div class="drImg"><img src="images/alertImg.png"></div>
			<div style="height:70px;"></div>
		</td>
		</tr>
	</table>
<!--[if lte IE 6.5]><iframe class="hackiframe"></iframe><![endif]-->
</div>

<div id="Loading" class="popup_bg"></div>

<iframe name="hidden_frame" id="hidden_frame" src="" width="0" height="0" frameborder="0"></iframe>

<form method="post" name="form" id="ruleForm" action="/start_apply.htm" target="hidden_frame">
<input type="hidden" name="productid" value="<% nvram_get("productid"); %>">
<input type="hidden" name="current_page" value="Advanced_SwitchCtrl_Content.asp">
<input type="hidden" name="next_page" value="">
<input type="hidden" name="group_id" value="">
<input type="hidden" name="modified" value="0">
<input type="hidden" name="action_mode" value="apply_new">
<input type="hidden" name="action_script" value="restart_allnet">
<input type="hidden" name="action_wait" value="30">
<input type="hidden" name="preferred_lang" id="preferred_lang" value="<% nvram_get("preferred_lang"); %>">
<input type="hidden" name="firmver" value="<% nvram_get("firmver"); %>">

<table class="content" align="center" cellpadding="0" cellspacing="0">
  <tr>
	<td width="17">&nbsp;</td>
	
	<!--=====Beginning of Main Menu=====-->
	<td valign="top" width="202">
	  <div id="mainMenu"></div>
	  <div id="subMenu"></div>
	</td>
	
    <td valign="top">
	<div id="tabMenu" class="submenuBlock"></div>
		<!--===================================Beginning of Main Content===========================================-->
<table width="98%" border="0" align="left" cellpadding="0" cellspacing="0">
	<tr>
		<td align="left" valign="top">
  <table width="760px" border="0" cellpadding="5" cellspacing="0" class="FormTitle" id="FormTitle">
	<tbody>
	<tr>
		  <td bgcolor="#4D595D" valign="top"  >
		  <div>&nbsp;</div>
		  <div class="formfonttitle"><#menu5_2#> - <#Switch_itemname#></div>
      <div style="margin:10px 0 10px 5px;" class="splitLine"></div>
      <div class="formfontdesc"><#SwitchCtrl_desc#></div>
		  
		  <table width="100%" border="1" align="center" cellpadding="4" cellspacing="0" bordercolor="#6b8fa3"  class="FormTable">
		  	
			<tr>
					<th><a class="hintstyle" href="javascript:void(0);" onClick="openHint(6, 7);"><#RouterConfig_GWMulticast_unknownUni_itemname#></a></th>
        	<td><!-- valid_muliticast(); -->
          	<input type="text" maxlength="4" class="input_6_table" id="switch_ctrlrate_unknown_unicast" name="switch_ctrlrate_unknown_unicast" value="<% nvram_get("switch_ctrlrate_unknown_unicast"); %>" onkeypress="return validator.isNumber(this, event);" autocorrect="off" autocapitalize="off">
          </td>
			</tr>

				<tr>
					<th><a class="hintstyle" href="javascript:void(0);" onClick="openHint(6, 7);"><#RouterConfig_GWMulticast_unknownMul_itemname#></a></th>
        	<td>
          	<input type="text" maxlength="4" class="input_6_table" id="switch_ctrlrate_unknown_multicast" name="switch_ctrlrate_unknown_multicast" value="<% nvram_get("switch_ctrlrate_unknown_multicast"); %>" onkeypress="return validator.isNumber(this, event);" autocorrect="off" autocapitalize="off">
          </td>
				</tr>

				<tr>
					<th><a class="hintstyle" href="javascript:void(0);" onClick="openHint(6, 7);"><#RouterConfig_GWMulticast_Multicast_itemname#></a></th>
        	<td>
          	<input type="text" maxlength="4" class="input_6_table" id="switch_ctrlrate_multicast" name="switch_ctrlrate_multicast" value="<% nvram_get("switch_ctrlrate_multicast"); %>" onkeypress="return validator.isNumber(this, event);" autocorrect="off" autocapitalize="off">
          </td>
				</tr>

				<tr>
					<th><a class="hintstyle" href="javascript:void(0);" onClick="openHint(6, 7);"><#RouterConfig_GWMulticast_Broadcast_itemname#></a></th>
        	<td>
          	<input type="text" maxlength="4" class="input_6_table" id="switch_ctrlrate_broadcast" name="switch_ctrlrate_broadcast" value="<% nvram_get("switch_ctrlrate_broadcast"); %>" onkeypress="return validator.isNumber(this, event);" autocorrect="off" autocapitalize="off">
          </td>
				</tr>
      	<tr>
      		<th><#NAT_Acceleration#></th>
          <td>
		<select name="hwnat" class="input_option">
			<option class="content_input_fd" value="0" <% nvram_match("hwnat", "0","selected"); %>><#WLANConfig11b_WirelessCtrl_buttonname#></option>
			<option class="content_input_fd" value="1" <% nvram_match("hwnat", "1","selected"); %>><#Auto#></option>
		</select>
		&nbsp
		<span id="natAccelDesc"></span>
          </td>
      	</tr>					
		</table>	

		<div class="apply_gen">
			<input class="button_gen" onclick="applyRule()" type="button" value="<#CTL_apply#>"/>
		</div>
		
	  </td>
	</tr>

	</tbody>	
  </table>		
					
		</td>
	</form>					
				</tr>
			</table>				
			<!--===================================End of Main Content===========================================-->
</td>

    <td width="10" align="center" valign="top">&nbsp;</td>
	</tr>
</table>

<div id="footer"></div>
</body>
</html>
