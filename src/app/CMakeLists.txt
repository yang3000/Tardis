set( CORE_SOURCE_FILES
    #Application.cpp
    Test.cpp
    ../core/SpdLog.cpp 
    ../core/DynamicModule.cpp 
    ../core/RapidJsonParser.cpp 
    ../core/JsonParser.cpp 
    ../core/RawDataContainer.cpp
    ../core/Runner.cpp
    ../core/Engine.cpp
    ../ui/imgui/imgui.cpp
    ../ui/imgui/imgui_widgets.cpp
    ../ui/imgui/imgui_tables.cpp
    ../ui/imgui/imgui_draw.cpp
    ../ui/imgui/imgui_impl_win32.cpp
    ../ui/imgui/imgui_impl_dx12.cpp
    ../ui/DirectX12Device.cpp
    ../ui/WindowEditor.cpp
    ../ui/Canvas.cpp
    ../ui/panel/APanel.cpp
    ../ui/AWidget.cpp
    ../ui/panel/PanelMenuBar.cpp
    ../ui/panel/PanelSequenceEditor.cpp
)
#add_executable(main main.cpp  ${CORE_SOURCE_FILES})
#add_executable(tardis Tardis.cpp  ${CORE_SOURCE_FILES})
add_executable(tardis Test.cpp  ${CORE_SOURCE_FILES})

target_link_libraries(tardis DbgHelp.lib d3d12.lib d3dcompiler.lib dxgi.lib)
