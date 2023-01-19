set( CORE_SOURCE_FILES
    Application.cpp
    ../core/SpdLog.cpp 
    ../core/DynamicModule.cpp 
    ../core/RapidJsonParser.cpp 
    ../core/JsonParser.cpp 
    ../core/RawDataContainer.cpp
    ../core/Runner.cpp
    ../core/Engine.cpp
    ../core/PluginManager.cpp
    ../ui/imgui/imgui.cpp
    ../ui/imgui/imgui_widgets.cpp
    ../ui/imgui/imgui_tables.cpp
    ../ui/imgui/imgui_draw.cpp
    ../ui/imgui/imgui_impl_win32.cpp
    ../ui/imgui/imgui_impl_dx12.cpp
    ../ui/DirectX12Device.cpp
    ../ui/WindowEditor.cpp
    ../ui/WindowTestStand.cpp
    ../ui/Canvas.cpp
    ../ui/PanelsManager.cpp
    ../ui/panel/APanel.cpp

    ../ui/AWidget.cpp
    ../ui/WidgetContainer.cpp

    ../ui/layout/Collapsing.cpp
    ../ui/layout/CollapsingEx.cpp
    ../ui/layout/GroupSameline.cpp
    ../ui/layout/GroupChild.cpp
    ../ui/layout/TreeNode.cpp
    ../ui/layout/PopupWindow.cpp
    ../ui/layout/Group.cpp
    
    ../ui/widgets/WidgetRunnerProperty.cpp
    ../ui/widgets/CheckBox.cpp
    ../ui/widgets/Text.cpp
    ../ui/widgets/LabelText.cpp
    ../ui/widgets/Separator.cpp
    ../ui/widgets/Spacing.cpp
    ../ui/widgets/TextColored.cpp
    ../ui/widgets/Button.cpp
    ../ui/widgets/InputText.cpp
    ../ui/widgets/ComboBox.cpp
    ../ui/widgets/HelperMarker.cpp
    ../ui/widgets/DragSingleScalar.cpp
    ../ui/widgets/DragScalarRange.cpp
    ../ui/widgets/Caller.cpp
    ../ui/widgets/NewPlugin.cpp
    ../ui/widgets/TestItemList.cpp
    
    ../ui/panel/PanelWindow.cpp
    ../ui/panel/PanelMenuBar.cpp
    ../ui/panel/PanelSequenceEditor.cpp
    ../ui/panel/PanelTestStand.cpp
    ../ui/panel/PanelProperties.cpp
    ../ui/panel/PanelPluginManager.cpp
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/test)

#add_executable(main main.cpp  ${CORE_SOURCE_FILES})
add_executable(tardis Tardis.cpp  ${CORE_SOURCE_FILES})
# add_executable(tardis Test.cpp  ${CORE_SOURCE_FILES})

target_link_libraries(tardis DbgHelp.lib d3d12.lib d3dcompiler.lib dxgi.lib)
