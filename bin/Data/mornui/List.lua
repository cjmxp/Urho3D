local List = UI_List:new()
List:SetXml([[<List x="483" y="124" repeatX="5" repeatY="5" spaceX="5" spaceY="10" var="list" width="465" height="469">
<Box name="render" x="0" y="0" width="100" height="100">
  <Clip skin="Textures/image.png" index="0" clipX="2" width="100" height="100" name="img"/>
</Box>
<VScrollBar skin="Textures/vscroll.png" x="448" width="17" height="469" name="scrollBar"/>
</List>]])
List:InitAttribute()
List:InitChilds()
return List