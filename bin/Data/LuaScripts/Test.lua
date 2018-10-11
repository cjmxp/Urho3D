-- A simple 'HelloWorld' GUI created purely from code.
-- This sample demonstrates:
--     - Creation of controls and building a UI hierarchy
--     - Loading UI style from XML and applying it to controls
--     - Handling of global and per-control events
-- For more advanced users (beginners can skip this section):
--     - Dragging UIElements
--     - Displaying tooltips
--     - Accessing available Events data (eventData)

require "LuaScripts/Utilities/Sample"

local window = nil
local dragBeginPosition = IntVector2(0, 0)

function Start()
    -- Execute the common startup for samples
    SampleStart()

    -- Enable OS cursor
    input.mouseVisible = true

    -- Load XML file containing default UI style sheet
    local style = cache:GetResource("XMLFile", "UI/DefaultStyle.xml")

    -- Set the loaded style as default style
    ui.root.defaultStyle = style

    -- Initialize Window

    -- Create and add some controls to the Window
    InitControls()

    -- Create a draggable Fish
    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
end

function InitControls()
    local text = RichText:new()
    text:SetText([[<img src="Urho2D/Ball.png" />tcp test <text color=0xff0000ff font="Fonts/Anonymous Pro.ttf" size=50>123123123]])
    text:SetMinSize(1000, 500)
    text:SetSize(1000, 500)
    ui.root:AddChild(text)

    ui:DebugDraw(text)
end
