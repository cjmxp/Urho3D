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
    InitWindow()

    -- Create and add some controls to the Window
    InitControls()

    -- Create a draggable Fish
    -- Set the mouse mode to use in the sample
    SampleInitMouseMode(MM_FREE)
end

function InitControls()
    -- Create a CheckBox
    -- local checkBox = CheckBox:new()
    -- checkBox:SetName("CheckBox")

    -- Create a Button
    local button = Button:new()
    button:SetName("Button")
    button.minHeight = 24

    local text = Text:new()
    text.name = "WindowTitle"
    text.text = 'tcp test'
    button:AddChild(text)

    -- Create a LineEdit
    -- local lineEdit = LineEdit:new()
    -- lineEdit:SetName("LineEdit")
    -- lineEdit.minHeight = 24

    -- Add controls to Window
    -- window:AddChild(checkBox)
    window:AddChild(button)
    -- window:AddChild(lineEdit)

    -- Apply previously set default style
    text:SetStyleAuto()
    button:SetStyleAuto()
    -- lineEdit:SetStyleAuto()
end

function InitWindow()
    -- Create the Window and add it to the UI's root node
    window = Window:new()
    ui.root:AddChild(window)

    -- Set Window size and layout settings
    window.minWidth = 384
    window:SetLayout(LM_VERTICAL, 6, IntRect(6, 6, 6, 6))
    window:SetAlignment(HA_CENTER, VA_CENTER)
    window:SetName("Window")

    -- Create Window 'titlebar' container
    local titleBar = UIElement:new()
    titleBar:SetMinSize(0, 24)
    titleBar.verticalAlignment = VA_TOP
    titleBar.layoutMode = LM_HORIZONTAL

    -- Create the Window title Text
    local windowTitle = Text:new()
    windowTitle.name = "WindowTitle"
    windowTitle.text = "Hello GUI!"


    -- Create the Window's close button
    local buttonClose = Button:new()
    buttonClose:SetName("CloseButton")

    -- Add the controls to the title bar
    titleBar:AddChild(windowTitle)
    titleBar:AddChild(buttonClose)

    -- Add the title bar to the Window
    window:AddChild(titleBar)


    -- Apply styles
    window:SetStyleAuto()
    windowTitle:SetStyleAuto()
    buttonClose:SetStyle("CloseButton")

    -- Subscribe to buttonClose release (following a 'press') events
    SubscribeToEvent(buttonClose, "Released",
        function (eventType, eventData)
            engine:Exit()
        end)

    -- Subscribe also to all UI mouse clicks just to see where we have clicked
    SubscribeToEvent("UIMouseClick", HandleControlClicked)
end

function HandleControlClicked(eventType, eventData)
    print(fileSystem:GetProgramDir())
    print(fileSystem:GetUserDocumentsDir())
    print(fileSystem:GetAppPreferencesDir())
    print(fileSystem:GetTemporaryDir())
    print(tcp)
    if not tcp then
        http:Get('http://coolaf.com/static/js/ie-emulation-modes-warning.js')
        http:SycGet('http://libs.baidu.com/bootstrap/3.0.3/css/bootstrap.min.css')
        http:SycGet('http://libs.baidu.com/jquery/1.9.1/jquery.min.js')
        
        SubscribeToEvent('RequestOK', function(_, e)
            if e.Buffer then
                local buffer = e.Buffer:GetVoidPtr('VectorBuffer')
                print(buffer:ReadString())
            else
                --print('download ok', e.Filepath:GetString())
            end
        end)
        SubscribeToEvent('RequestErr', function(_, e)
            local buffer = e.Message:GetString()
            print(buffer)
        end)
        local arr = fileSystem:ScanDir("./","*.*",SCAN_FILES,false)
        --for i, v in ipairs(arr) do
        --    print(i, v)
        --end 
        -- tcp = TcpConn()
        -- tcp:Connect('127.0.0.1',8888)
        -- SubscribeToEvent(tcp, 'TcpConnected', function(_, e)
        --     print('123123123')
        --     Log:WriteRaw('123123321')
        -- end)

        -- SubscribeToEvent(tcp, 'TcpData', function(_, e)
        --     local buffer = e["Data"]:GetVoidPtr("VectorBuffer")
        --     Log:WriteRaw(tolua.type(buffer))
        --     Log:WriteRaw('<<<<<'.. buffer:ReadString())
        -- end)
    end

    -- Get the Text control acting as the Window's title
    local element = window:GetChild("WindowTitle", true)
    local windowTitle = tolua.cast(element, 'Text')

    -- Get control that was clicked
    local clicked = eventData["Element"]:GetPtr("UIElement")
    local name = "...?"
    if clicked ~= nil then
        -- Get the name of the control that was clicked
        name = clicked.name
    end

    -- Update the Window's title text
    windowTitle.text = "Hello " .. name .. "!"
end

