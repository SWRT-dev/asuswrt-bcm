﻿<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<meta HTTP-EQUIV="Pragma" CONTENT="no-cache">
<meta HTTP-EQUIV="Expires" CONTENT="-1">
<link rel="shortcut icon" href="images/favicon.png">
<link rel="icon" href="images/favicon.png">
<script type="text/javascript" src="/disk_msg.js"></script>
<script type="text/javascript">
function create_sharedfolder_error(error_msg){
	parent.alert_error_msg(error_msg);
}

function create_sharedfolder_success(){
	if(parent.document.form.current_page.value != "mediaserver.asp" && parent.document.form.current_page.value != "cloud_sync.asp" && parent.document.form.current_page.value != "cloud_router_sync.asp")
		parent.refreshpage();
}
</script>
</head>

<body>
<% create_sharedfolder(); %>
</body>
</html>
