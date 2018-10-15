-- This first example, maintaining tradition, prints a "Hello World" message.
-- Furthermore it shows:
--     - Using the Sample utility functions as a base for the application
--     - Adding a Text element to the graphical user interface
--     - Subscribing to and handling of update events

require "LuaScripts/Utilities/Sample"

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Create "Hello World" Text
    CreateText()

    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)

    -- Finally, hook-up this HelloWorld instance to handle update events
    SubscribeToEvents()
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
    local uiStyle = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")
    -- Set style to the UI root so that elements will inherit it
    ui.root.defaultStyle = uiStyle
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

    local checkBox = UI_CheckBox:new()
    checkBox:SetPosition(150,50)
    checkBox.clipX=1;
    checkBox.clipY=3;
    checkBox.lable="测试"
    checkBox:SetSizeGrid("1 1 1 1")
    checkBox:SetSkin("Textures/checkbox.png")
    ui.root:AddChild(checkBox)

    local radio = UI_Radio:new()
    radio:SetPosition(200,50)
    radio.clipX=1;
    radio.clipY=3;
    radio.lable="测试"
    radio:SetSizeGrid("1 1 1 1")
    radio:SetSkin("Textures/radio.png")
    ui.root:AddChild(radio)


end

function Click(type,event)
    print("=====")
end
function SubscribeToEvents()
   
    -- Subscribe HandleUpdate() function for processing update events
    --SubscribeToEvent("Update", "HandleUpdate")
    --SubscribeToEvent(clip,"Click", "Click")
    
end

function HandleUpdate(eventType, eventData)
    --frame(eventData["TimeStep"]:GetFloat())
    
    -- Do nothing for now, could be extended to eg. animate the display
end
function frame(timeStep)
    time=time+timeStep
    if time>0.8 then
        time=0.0
        --clip.index = clip.index+1
    end
    
end
-- Create XML patch instructions for screen joystick layout specific to this sample app
function GetScreenJoystickPatchString()
    return
        "<patch>" ..
        "    <add sel=\"/element/element[./attribute[@name='Name' and @value='Hat0']]\">" ..
        "        <attribute name=\"Is Visible\" value=\"false\" />" ..
        "    </add>" ..
        "</patch>"
end
