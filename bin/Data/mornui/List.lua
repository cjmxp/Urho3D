--代码由编辑器生成，逻辑编码必须在子类实现
local LoginUI = UI_View:new()
LoginUI:SetXml([[<View width="1024" height="768">
<Image skin="gameui/login_bg.png" x="0" y="0" width="1024" height="768" mouseChildren="false" mouseEnabled="false"/>
<Box x="-141" y="324" var="xj" width="1282" height="353" mouseChildren="false" mouseEnabled="false">
  <Image skin="gameui/logint_ree.png" y="167" x="0" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="76" y="162" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="217" y="158" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="1010" y="127" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="162" y="187" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="956" y="86" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="950" y="148" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="906" y="142" width="272" height="161"/>
  <Image skin="gameui/logint_ree.png" x="980" y="192" width="272" height="161"/>
  <Image skin="gameui/logint_bg3.png" x="87" y="0" width="1171" height="346"/>
</Box>
<Image skin="gameui/logint_bg1.png" x="-177" y="343" width="679" height="324" var="zj" mouseChildren="false" mouseEnabled="false"/>
<Image skin="gameui/logint_bg0.png" x="-193" y="415" width="1344" height="388" var="qj" mouseChildren="false" mouseEnabled="false"/>
<Image skin="gameui/logint_y0.png" x="-110" y="375" width="477" height="61" var="ly" mouseChildren="false" mouseEnabled="false"/>
<Image skin="gameui/logint_y2.png" x="637" y="451" width="497" height="74" var="ry" mouseChildren="false" mouseEnabled="false"/>
<Image skin="gameui/logint_y1.png" x="45" y="582" width="496" height="97" var="by" mouseChildren="false" mouseEnabled="false"/>
<Image skin="gameui/login_box.png" x="377" y="302" width="270" height="395" mouseChildren="false" mouseEnabled="false"/>
<TextInput x="451" y="452" width="164" height="21" color="0xffffff" align="left" size="14" var="user"/>
<TextInput x="452" y="489" width="164" height="21" color="0xffffff" asPassword="true" size="14" var="pwd"/>
<CheckBox skin="gameui/check.png" x="424" y="528" width="19" height="19" spread="true" name="记住账号"/>
<CheckBox skin="gameui/check.png" x="523" y="528" width="19" height="19" spread="true" name="强行登录"/>
<Button skin="gameui/btn_server.png" x="434" y="566" width="162" height="34" spread="true" name="服务器列表"/>
<Button skin="gameui/btn_start.png" x="434" y="610" width="162" height="34" spread="true" name="开始游戏"/>
</View>]])
LoginUI:InitAttribute()
LoginUI:InitChilds()

return LoginUI