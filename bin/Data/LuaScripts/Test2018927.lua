-- This first example, maintaining tradition, prints a "Hello World" message.
-- Furthermore it shows:
--     - Using the Sample utility functions as a base for the application
--     - Adding a Text element to the graphical user interface
--     - Subscribing to and handling of update events
--require "LuaScripts/Utilities/Sample"



function Start()
    -- Execute the common startup for samples
    --SampleStart()
    -- Create "Hello World" Text
    CreateText()
    input.mouseVisible = true
    local Debug = require("LuaScripts/utils/Debug")
    Debug:InitConsole();
    -- Finally, hook-up this HelloWorld instance to handle update events
   -- SubscribeToEvents()
end

function CreateText()
    -- Construct new Text object
   --[[
    clip = Clip:new()
    local decalTex = cache:GetResource("Texture2D", "Textures/bg.png")
    
    -- Add Text instance to the UI root element
    --clip.clipX=4
    --clip.clipY=4
    clip.texture = decalTex
    clip:SetSize(400,400)
    clip.sizeGrid=IntRect(5,30,5,5)
    clip:Margin(0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF,0x7FFFFFFF)
    clip.enabled=true
    clip.scale=Vector2(0.5,0.5)
    cc = Box:new()
    cc:SetSize(500,500)
    cc:AddChild(clip)
    ui.root:AddChild(cc)
    time = 0.0
    Log:WriteRaw(cc:GetParent().GetSize())

   ]]--
--[[
    local button = UI_Button:new()
    button.clipX=1;
    button.clipY=3;
    button:SetSize(60,30)
    button:SetLable("按钮")
    button:SetSizeGrid("1 1 1 1")
    button:SetSkin("Textures/button.png")
    button:SetPosition(300,50)

    ui.root:AddChild(button)
    local text = LineEdit:new()
    text:SetPosition(100,0)
    text.name = "Text"
    text.text = "Hello GUI!"
    text.enabled=true
    text.selected=true
    text.editable=true
    text:SetSize(500,30)
    text:SetStyleAuto()
    text.textElement.selectionColor=Color(0, 0, 0, 1)
    text.textElement.color=Color(1, 0, 0, 1)
    ui.root:AddChild(text)
]]--
--[[
    local checkBox = UI_CheckBox:new()
    checkBox:SetPosition(100,0)
    checkBox.clipX=1;
    checkBox.clipY=3;
    checkBox.lable="测试"
    checkBox:SetSizeGrid("1 1 1 1")
    checkBox:SetSkin("Textures/checkbox.png")
    
    
    local radio = UI_Radio:new()
    
    radio.clipX=1;
    radio.clipY=3;
    radio.lable="测试"
    radio:SetSizeGrid("1 1 1 1")
    radio:SetSkin("Textures/radio.png")
    radio:SetPosition(100,50)
   

    local group = UI_RadioGroup:new()
    group.clipX=1
    group.clipY=3
    group.skin="Textures/radio.png"
    group.selectedIndex=0
    group.direction=1
    group.space=5;
    group.sizeGrid="0 0 0 0"
    group.labels="测试1,测试2,测试3"
    group:SetPosition(100,100)
    

    local button = UI_Button:new()
    button.clipX=1;
    button.clipY=3;
    button:SetSize(60,30)
    button:SetLable("按钮")
    button:SetSizeGrid("1 1 1 1")
    button:SetSkin("Textures/button.png")
    button:SetPosition(100,150)
    --box:AddChild(clip)
    --box:AddChild(group)
    
    local clip = UI_Clip:new()
    clip.skin="Textures/bg.png"
    clip.sizeGrid="5 30 5 5"
    clip:SetPosition(100,200)
    clip:SetSize(200,200)
]]--
    local box = require("mornui/List")
    ui.root:AddChild(box)
    box2 = require("mornui/List2")
    box2:Show()


end





