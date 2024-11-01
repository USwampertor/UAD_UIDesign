#include "uiEditorUI.h"

#include "uiApp.h"
#include "uiAnimator.h"
#include "uiInputManager.h"
#include "uiClassRegisters.h"
#include "uiLogger.h"
#include "uiResourceManager.h"
#include "uiSceneManager.h"
#include "uiTexture.h"
#include "uiUtilities.h"
#include "uiVector2.h"


#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"
#include "ImGuiFileDialog.h"
#include "imspinner.h"

struct ExampleSelectionWithDeletion : ImGuiSelectionBasicStorage
{
  // Find which item should be Focused after deletion.
  // Call _before_ item submission. Retunr an index in the before-deletion item list, your item loop should call SetKeyboardFocusHere() on it.
  // The subsequent ApplyDeletionPostLoop() code will use it to apply Selection.
  // - We cannot provide this logic in core Dear ImGui because we don't have access to selection data.
  // - We don't actually manipulate the ImVector<> here, only in ApplyDeletionPostLoop(), but using similar API for consistency and flexibility.
  // - Important: Deletion only works if the underlying ImGuiID for your items are stable: aka not depend on their index, but on e.g. item id/ptr.
  // FIXME-MULTISELECT: Doesn't take account of the possibility focus target will be moved during deletion. Need refocus or scroll offset.
  int ApplyDeletionPreLoop(ImGuiMultiSelectIO* ms_io, int items_count)
  {
    if (Size == 0)
      return -1;

    // If focused item is not selected...
    const int focused_idx = (int)ms_io->NavIdItem;  // Index of currently focused item
    if (ms_io->NavIdSelected == false)  // This is merely a shortcut, == Contains(adapter->IndexToStorage(items, focused_idx))
    {
      ms_io->RangeSrcReset = true;    // Request to recover RangeSrc from NavId next frame. Would be ok to reset even when NavIdSelected==true, but it would take an extra frame to recover RangeSrc when deleting a selected item.
      return focused_idx;             // Request to focus same item after deletion.
    }

    // If focused item is selected: land on first unselected item after focused item.
    for (int idx = focused_idx + 1; idx < items_count; idx++)
      if (!Contains(GetStorageIdFromIndex(idx)))
        return idx;

    // If focused item is selected: otherwise return last unselected item before focused item.
    for (int idx = std::min(focused_idx, items_count) - 1; idx >= 0; idx--)
      if (!Contains(GetStorageIdFromIndex(idx)))
        return idx;

    return -1;
  }

  // Rewrite item list (delete items) + update selection.
  // - Call after EndMultiSelect()
  // - We cannot provide this logic in core Dear ImGui because we don't have access to your items, nor to selection data.
  template<typename ITEM_TYPE>
  void ApplyDeletionPostLoop(ImGuiMultiSelectIO* ms_io, ImVector<ITEM_TYPE>& items, int item_curr_idx_to_select)
  {
    // Rewrite item list (delete items) + convert old selection index (before deletion) to new selection index (after selection).
    // If NavId was not part of selection, we will stay on same item.
    ImVector<ITEM_TYPE> new_items;
    new_items.reserve(items.Size - Size);
    int item_next_idx_to_select = -1;
    for (int idx = 0; idx < items.Size; idx++)
    {
      if (!Contains(GetStorageIdFromIndex(idx)))
        new_items.push_back(items[idx]);
      if (item_curr_idx_to_select == idx)
        item_next_idx_to_select = new_items.Size - 1;
    }
    items.swap(new_items);

    // Update selection
    Clear();
    if (item_next_idx_to_select != -1 && ms_io->NavIdSelected)
      SetItemSelected(GetStorageIdFromIndex(item_next_idx_to_select), true);
  }
};

struct ExampleAsset
{
  ImGuiID ID;
  int     Type;

  ExampleAsset(ImGuiID id, int type) { ID = id; Type = type; }

  static const ImGuiTableSortSpecs* s_current_sort_specs;

  static void SortWithSortSpecs(ImGuiTableSortSpecs* sort_specs, ExampleAsset* items, int items_count)
  {
    s_current_sort_specs = sort_specs; // Store in variable accessible by the sort function.
    if (items_count > 1)
      qsort(items, (size_t)items_count, sizeof(items[0]), ExampleAsset::CompareWithSortSpecs);
    s_current_sort_specs = NULL;
  }

  // Compare function to be used by qsort()
  static int IMGUI_CDECL CompareWithSortSpecs(const void* lhs, const void* rhs)
  {
    const ExampleAsset* a = (const ExampleAsset*)lhs;
    const ExampleAsset* b = (const ExampleAsset*)rhs;
    for (int n = 0; n < s_current_sort_specs->SpecsCount; n++)
    {
      const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
      int delta = 0;
      if (sort_spec->ColumnIndex == 0)
        delta = ((int)a->ID - (int)b->ID);
      else if (sort_spec->ColumnIndex == 1)
        delta = (a->Type - b->Type);
      if (delta > 0)
        return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
      if (delta < 0)
        return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
    }
    return ((int)a->ID - (int)b->ID);
  }
};


struct ExampleAssetsBrowser
{
  // Options
  bool            ShowTypeOverlay = true;
  bool            AllowSorting = true;
  bool            AllowDragUnselected = false;
  bool            AllowBoxSelect = true;
  float           IconSize = 32.0f;
  int             IconSpacing = 10;
  int             IconHitSpacing = 4;         // Increase hit-spacing if you want to make it possible to clear or box-select from gaps. Some spacing is required to able to amend with Shift+box-select. Value is small in Explorer.
  bool            StretchSpacing = true;

  // State
  ImVector<ExampleAsset> Items;               // Our items
  ExampleSelectionWithDeletion Selection;     // Our selection (ImGuiSelectionBasicStorage + helper funcs to handle deletion)
  ImGuiID         NextItemId = 0;             // Unique identifier when creating new items
  bool            RequestDelete = false;      // Deferred deletion request
  bool            RequestSort = false;        // Deferred sort request
  float           ZoomWheelAccum = 0.0f;      // Mouse wheel accumulator to handle smooth wheels better

  // Calculated sizes for layout, output of UpdateLayoutSizes(). Could be locals but our code is simpler this way.
  ImVec2          LayoutItemSize;
  ImVec2          LayoutItemStep;             // == LayoutItemSize + LayoutItemSpacing
  float           LayoutItemSpacing = 0.0f;
  float           LayoutSelectableSpacing = 0.0f;
  float           LayoutOuterPadding = 0.0f;
  int             LayoutColumnCount = 0;
  int             LayoutLineCount = 0;

  // Functions
  ExampleAssetsBrowser()
  {
    AddItems(10000);
  }
  void AddItems(int count)
  {
    if (Items.Size == 0)
      NextItemId = 0;
    Items.reserve(Items.Size + count);
    for (int n = 0; n < count; n++, NextItemId++)
      Items.push_back(ExampleAsset(NextItemId, (NextItemId % 20) < 15 ? 0 : (NextItemId % 20) < 18 ? 1 : 2));
    RequestSort = true;
  }
  void ClearItems()
  {
    Items.clear();
    Selection.Clear();
  }

  // Logic would be written in the main code BeginChild() and outputing to local variables.
  // We extracted it into a function so we can call it easily from multiple places.
  void UpdateLayoutSizes(float avail_width)
  {
    // Layout: when not stretching: allow extending into right-most spacing.
    LayoutItemSpacing = (float)IconSpacing;
    if (StretchSpacing == false)
      avail_width += floorf(LayoutItemSpacing * 0.5f);

    // Layout: calculate number of icon per line and number of lines
    LayoutItemSize = ImVec2(floorf(IconSize), floorf(IconSize));
    LayoutColumnCount = std::max((int)(avail_width / (LayoutItemSize.x + LayoutItemSpacing)), 1);
    LayoutLineCount = (Items.Size + LayoutColumnCount - 1) / LayoutColumnCount;

    // Layout: when stretching: allocate remaining space to more spacing. Round before division, so item_spacing may be non-integer.
    if (StretchSpacing && LayoutColumnCount > 1)
      LayoutItemSpacing = floorf(avail_width - LayoutItemSize.x * LayoutColumnCount) / LayoutColumnCount;

    LayoutItemStep = ImVec2(LayoutItemSize.x + LayoutItemSpacing, LayoutItemSize.y + LayoutItemSpacing);
    LayoutSelectableSpacing = std::max(floorf(LayoutItemSpacing) - IconHitSpacing, 0.0f);
    LayoutOuterPadding = floorf(LayoutItemSpacing * 0.5f);
  }

  void Draw()
  {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowContentSize(ImVec2(0.0f, LayoutOuterPadding + LayoutLineCount * (LayoutItemSize.x + LayoutItemSpacing)));
    if (ImGui::BeginChild("Assets", ImVec2(0.0f, -ImGui::GetTextLineHeightWithSpacing()), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoMove))
    {
      ImDrawList* draw_list = ImGui::GetWindowDrawList();

      const float avail_width = ImGui::GetContentRegionAvail().x;
      UpdateLayoutSizes(avail_width);

      // Calculate and store start position.
      ImVec2 start_pos = ImGui::GetCursorScreenPos();
      start_pos = ImVec2(start_pos.x + LayoutOuterPadding, start_pos.y + LayoutOuterPadding);
      ImGui::SetCursorScreenPos(start_pos);

      // Multi-select
      ImGuiMultiSelectFlags ms_flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_ClearOnClickVoid;

      // - Enable box-select (in 2D mode, so that changing box-select rectangle X1/X2 boundaries will affect clipped items)
      if (AllowBoxSelect)
        ms_flags |= ImGuiMultiSelectFlags_BoxSelect2d;

      // - This feature allows dragging an unselected item without selecting it (rarely used)
      if (AllowDragUnselected)
        ms_flags |= ImGuiMultiSelectFlags_SelectOnClickRelease;

      // - Enable keyboard wrapping on X axis
      // (FIXME-MULTISELECT: We haven't designed/exposed a general nav wrapping api yet, so this flag is provided as a courtesy to avoid doing:
      //    ImGui::NavMoveRequestTryWrapping(ImGui::GetCurrentWindow(), ImGuiNavMoveFlags_WrapX);
      // When we finish implementing a more general API for this, we will obsolete this flag in favor of the new system)
      ms_flags |= ImGuiMultiSelectFlags_NavWrapX;

      ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(ms_flags, Selection.Size, Items.Size);

      // Use custom selection adapter: store ID in selection (recommended)
      Selection.UserData = this;
      Selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self_, int idx) { ExampleAssetsBrowser* self = (ExampleAssetsBrowser*)self_->UserData; return self->Items[idx].ID; };
      Selection.ApplyRequests(ms_io);

      const bool want_delete = (ImGui::Shortcut(ImGuiKey_Delete, ImGuiInputFlags_Repeat) && (Selection.Size > 0)) || RequestDelete;
      const int item_curr_idx_to_focus = want_delete ? Selection.ApplyDeletionPreLoop(ms_io, Items.Size) : -1;
      RequestDelete = false;

      // Push LayoutSelectableSpacing (which is LayoutItemSpacing minus hit-spacing, if we decide to have hit gaps between items)
      // Altering style ItemSpacing may seem unnecessary as we position every items using SetCursorScreenPos()...
      // But it is necessary for two reasons:
      // - Selectables uses it by default to visually fill the space between two items.
      // - The vertical spacing would be measured by Clipper to calculate line height if we didn't provide it explicitly (here we do).
      ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(LayoutSelectableSpacing, LayoutSelectableSpacing));

      // Rendering parameters
      const ImU32 icon_type_overlay_colors[3] = { 0, IM_COL32(200, 70, 70, 255), IM_COL32(70, 170, 70, 255) };
      const ImU32 icon_bg_color = ImGui::GetColorU32(ImGuiCol_MenuBarBg);
      const ImVec2 icon_type_overlay_size = ImVec2(4.0f, 4.0f);
      const bool display_label = (LayoutItemSize.x >= ImGui::CalcTextSize("999").x);

      const int column_count = LayoutColumnCount;
      ImGuiListClipper clipper;
      clipper.Begin(LayoutLineCount, LayoutItemStep.y);
      if (item_curr_idx_to_focus != -1)
        clipper.IncludeItemByIndex(item_curr_idx_to_focus / column_count); // Ensure focused item line is not clipped.
      if (ms_io->RangeSrcItem != -1)
        clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem / column_count); // Ensure RangeSrc item line is not clipped.
      while (clipper.Step())
      {
        for (int line_idx = clipper.DisplayStart; line_idx < clipper.DisplayEnd; line_idx++)
        {
          const int item_min_idx_for_current_line = line_idx * column_count;
          const int item_max_idx_for_current_line = std::min((line_idx + 1) * column_count, Items.Size);
          for (int item_idx = item_min_idx_for_current_line; item_idx < item_max_idx_for_current_line; ++item_idx)
          {
            ExampleAsset* item_data = &Items[item_idx];
            ImGui::PushID((int)item_data->ID);

            // Position item
            ImVec2 pos = ImVec2(start_pos.x + (item_idx % column_count) * LayoutItemStep.x, start_pos.y + line_idx * LayoutItemStep.y);
            ImGui::SetCursorScreenPos(pos);

            ImGui::SetNextItemSelectionUserData(item_idx);
            bool item_is_selected = Selection.Contains((ImGuiID)item_data->ID);
            bool item_is_visible = ImGui::IsRectVisible(LayoutItemSize);
            ImGui::Selectable("", item_is_selected, ImGuiSelectableFlags_None, LayoutItemSize);

            // Update our selection state immediately (without waiting for EndMultiSelect() requests)
            // because we use this to alter the color of our text/icon.
            if (ImGui::IsItemToggledSelection())
              item_is_selected = !item_is_selected;

            // Focus (for after deletion)
            if (item_curr_idx_to_focus == item_idx)
              ImGui::SetKeyboardFocusHere(-1);

            // Drag and drop
            if (ImGui::BeginDragDropSource())
            {
              // Create payload with full selection OR single unselected item.
              // (the later is only possible when using ImGuiMultiSelectFlags_SelectOnClickRelease)
              if (ImGui::GetDragDropPayload() == NULL)
              {
                ImVector<ImGuiID> payload_items;
                void* it = NULL;
                ImGuiID id = 0;
                if (!item_is_selected)
                  payload_items.push_back(item_data->ID);
                else
                  while (Selection.GetNextSelectedItem(&it, &id))
                    payload_items.push_back(id);
                ImGui::SetDragDropPayload("ASSETS_BROWSER_ITEMS", payload_items.Data, (size_t)payload_items.size_in_bytes());
              }

              // Display payload content in tooltip, by extracting it from the payload data
              // (we could read from selection, but it is more correct and reusable to read from payload)
              const ImGuiPayload* payload = ImGui::GetDragDropPayload();
              const int payload_count = (int)payload->DataSize / (int)sizeof(ImGuiID);
              ImGui::Text("%d assets", payload_count);

              ImGui::EndDragDropSource();
            }

            // Render icon (a real app would likely display an image/thumbnail here)
            // Because we use ImGuiMultiSelectFlags_BoxSelect2d, clipping vertical may occasionally be larger, so we coarse-clip our rendering as well.
            if (item_is_visible)
            {
              ImVec2 box_min(pos.x - 1, pos.y - 1);
              ImVec2 box_max(box_min.x + LayoutItemSize.x + 2, box_min.y + LayoutItemSize.y + 2); // Dubious
              draw_list->AddRectFilled(box_min, box_max, icon_bg_color); // Background color
              if (ShowTypeOverlay && item_data->Type != 0)
              {
                ImU32 type_col = icon_type_overlay_colors[item_data->Type % IM_ARRAYSIZE(icon_type_overlay_colors)];
                draw_list->AddRectFilled(ImVec2(box_max.x - 2 - icon_type_overlay_size.x, box_min.y + 2), ImVec2(box_max.x - 2, box_min.y + 2 + icon_type_overlay_size.y), type_col);
              }
              if (display_label)
              {
                ImU32 label_col = ImGui::GetColorU32(item_is_selected ? ImGuiCol_Text : ImGuiCol_TextDisabled);
                char label[32];
                sprintf(label, "%d", item_data->ID);
                draw_list->AddText(ImVec2(box_min.x, box_max.y - ImGui::GetFontSize()), label_col, label);
              }
            }

            ImGui::PopID();
          }
        }
      }
      clipper.End();
      ImGui::PopStyleVar(); // ImGuiStyleVar_ItemSpacing

      // Context menu
      if (ImGui::BeginPopupContextWindow())
      {
        ImGui::Text("Selection: %d items", Selection.Size);
        ImGui::Separator();
        if (ImGui::MenuItem("Delete", "Del", false, Selection.Size > 0))
          RequestDelete = true;
        ImGui::EndPopup();
      }

      ms_io = ImGui::EndMultiSelect();
      Selection.ApplyRequests(ms_io);
      if (want_delete)
        Selection.ApplyDeletionPostLoop(ms_io, Items, item_curr_idx_to_focus);

      // Zooming with CTRL+Wheel
      if (ImGui::IsWindowAppearing())
        ZoomWheelAccum = 0.0f;
      if (ImGui::IsWindowHovered() && io.MouseWheel != 0.0f && ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsAnyItemActive() == false)
      {
        ZoomWheelAccum += io.MouseWheel;
        if (fabsf(ZoomWheelAccum) >= 1.0f)
        {
          // Calculate hovered item index from mouse location
          // FIXME: Locking aiming on 'hovered_item_idx' (with a cool-down timer) would ensure zoom keeps on it.
          const float hovered_item_nx = (io.MousePos.x - start_pos.x + LayoutItemSpacing * 0.5f) / LayoutItemStep.x;
          const float hovered_item_ny = (io.MousePos.y - start_pos.y + LayoutItemSpacing * 0.5f) / LayoutItemStep.y;
          const int hovered_item_idx = ((int)hovered_item_ny * LayoutColumnCount) + (int)hovered_item_nx;
          //ImGui::SetTooltip("%f,%f -> item %d", hovered_item_nx, hovered_item_ny, hovered_item_idx); // Move those 4 lines in block above for easy debugging

          // Zoom
          IconSize *= powf(1.1f, (float)(int)ZoomWheelAccum);
          IconSize = std::clamp(IconSize, 16.0f, 128.0f);
          ZoomWheelAccum -= (int)ZoomWheelAccum;
          UpdateLayoutSizes(avail_width);

          // Manipulate scroll to that we will land at the same Y location of currently hovered item.
          // - Calculate next frame position of item under mouse
          // - Set new scroll position to be used in next ImGui::BeginChild() call.
          float hovered_item_rel_pos_y = ((float)(hovered_item_idx / LayoutColumnCount) + fmodf(hovered_item_ny, 1.0f)) * LayoutItemStep.y;
          hovered_item_rel_pos_y += ImGui::GetStyle().WindowPadding.y;
          float mouse_local_y = io.MousePos.y - ImGui::GetWindowPos().y;
          ImGui::SetScrollY(hovered_item_rel_pos_y - mouse_local_y);
        }
      }
    }
    ImGui::EndChild();
    ImGui::Text("Selected: %d/%d items", Selection.Size, Items.Size);
  }
};

static ExampleAssetsBrowser assets_browser;


void EditorUI::Initialize()
{
  Logger::Instance().AddOnLogAddedCallback(std::bind(&EditorUI::AddDebuggerLog, 
                                                     this, 
                                                     std::placeholders::_1));
}

void EditorUI::AddDebuggerLog(const Log& newLog)
{
  if (newLog.m_flag == eLOGFLAG::DEBUGGER)
  {
    m_debugLogs.push_back(&newLog);
  }
}

void EditorUI::DrawUI()
{
  if (App::Instance().m_parser.HasFlag("editor"))
  {

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    if (ImGui::Begin("MainDock##1",
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_MenuBar |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus))
    {
      ImGui::PopStyleVar(3);
      if (ImGui::BeginMainMenuBar())
      {
        if (ImGui::BeginMenu("File"))
        {
          ImGui::MenuItem("New", "CTRL+N");
          ImGui::MenuItem("Save", "CTRL+S");
          ImGui::MenuItem("Save as", "CTRL+SHIFT+S");
          ImGui::MenuItem("Preferences", "");
          ImGui::MenuItem("Project Settings",
                          "CTRL+SHIFT+P",
                          &m_windowVisibilities["ProjectSettings"]);
          ImGui::EndMenu();
        }
        // 
        if (ImGui::BeginMenu("View"))
        {
          ImGui::MenuItem("Logger", "", &m_windowVisibilities["Logger"]);
          ImGui::MenuItem("Scene Graph", "", &m_windowVisibilities["SceneGraph"]);
          ImGui::MenuItem("Entity Inspector", "", &m_windowVisibilities["EntityInspector"]);
          ImGui::MenuItem("Resource Explorer", "", &m_windowVisibilities["Resources"]);
          ImGui::EndMenu();
        }
        //
        if (ImGui::BeginMenu("Editor"))
        {
          m_windowVisibilities["ViewportOptions"] = ImGui::MenuItem("Viewport Options", "");
          ImGui::EndMenu();
        }
        // 
        if (ImGui::BeginMenu("Create"))
        {
          if (ImGui::BeginMenu("Entities", ""))
          {
            for (auto it = ClassRegisters::GetEntityRegistry().begin();
                 it != ClassRegisters::GetEntityRegistry().end();
                 ++it)
            {
              ImGui::MenuItem(it->first.c_str());
            }
            ImGui::EndMenu();
          }
          ImGui::EndMenu();
        }
      }
      ImGui::EndMainMenuBar();


      ImGuiID dockSpaceID = ImGui::GetID("MainDock##2");

      ImGui::DockSpace(dockSpaceID,
                       ImVec2(0, 0),
                       ImGuiDockNodeFlags_PassthruCentralNode |
                       ImGuiDockNodeFlags_NoDockingOverCentralNode);

      /************************************************************************/
      /* Dockspace Start                                                      */
      /************************************************************************/
      if (m_windowVisibilities["ProjectSettings"])
      {
        if (ImGui::Begin("Project Settings"))
        {
          ImGui::Text("Project Settings");
          ImGui::Text("Name");
          ImGui::SameLine();
          ImGui::InputText("##ProjectName",
                           &App::Instance().m_editor->m_builder.m_settings.m_projectName,
                           ImGuiInputTextFlags_AlwaysOverwrite);
          ImGui::Text("Icon:");
          ImGui::SameLine();


          m_windowVisibilities["iconPopup"] = ImGui::ImageButton("IconImage##1",
            *ResourceManager::Instance().GetResource<Texture>(App::Instance().m_editor->m_builder.m_projectIconStr).get(),
            Vector2f(32.0f, 32.0f));
        }
        ImGui::Separator();

        ImGui::Text("Video Resolutions");

        for (int32 i = 0; i < App::Instance().m_editor->m_builder.m_settings.m_resolutions.size(); ++i)
        {
          String x = Utils::Format("%d",
                                   App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->width);
          String y = Utils::Format("%d",
                                   App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->height);
          ImGui::PushItemWidth(ImGui::GetWindowSize().x / 3);
          // ImGui::SetNextWindowContentSize(ImVec2(ImGui::GetWindowSize().x / 8, ImGui::CalcItemWidth()));
          ImGui::InputText(Utils::Format("##VideoResolution_%d_x", i).c_str(), &x[0], ImGuiInputTextFlags_CharsDecimal |
            ImGuiInputTextFlags_CharsNoBlank |
            ImGuiInputTextFlags_AlwaysOverwrite);
          // bool xisValid = !x.empty() && std::find_if(x.begin(), x.end(), [](unsigned char c) { return !std::isdigit(c); }) == x.end();
          x = Utils::IsStringNumber(x) ? x : "0";
          ImGui::SameLine();
          // ImGui::SetNextWindowContentSize(ImVec2(ImGui::GetWindowSize().x / 4, ImGui::CalcItemWidth()));
          ImGui::InputText(Utils::Format("##VideoResolution_%d_y", i).c_str(), &y[0], ImGuiInputTextFlags_CharsDecimal |
            ImGuiInputTextFlags_CharsNoBlank |
            ImGuiInputTextFlags_AlwaysOverwrite);
          // bool yisValid = !y.empty() && std::find_if(y.begin(), y.end(), [](unsigned char c) { return !std::isdigit(c); }) == y.end();
          y = Utils::IsStringNumber(y) ? y : "0";
          ImGui::PopItemWidth();

          App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->width = std::stoi(x);
          App::Instance().m_editor->m_builder.m_settings.m_resolutions[i]->height = std::stoi(y);
          ImGui::SameLine();

          if (ImGui::Button("x"))
          {
            App::Instance().m_editor->m_builder.m_settings.m_resolutions.erase(App::Instance().m_editor->m_builder.m_settings.m_resolutions.begin() + i);
            break;
          }
        }

        if (ImGui::Button("+"))
        {
          App::Instance().m_editor->m_builder.m_settings.m_resolutions.push_back(new VideoMode(0, 0));
        }

        ImGui::Separator();

        ImGui::Checkbox("Use vertical sync", &App::Instance().m_editor->m_builder.m_settings.m_shouldUseVerticalSync);

        String framerate = Utils::Format("%d", App::Instance().m_editor->m_builder.m_settings.m_framerate);
        ImGui::InputText("Framerate", &framerate[0], ImGuiInputTextFlags_CharsDecimal |
          ImGuiInputTextFlags_CharsNoBlank |
          ImGuiInputTextFlags_AlwaysOverwrite);
        framerate = Utils::IsStringNumber(framerate) ? framerate : "60";
        App::Instance().m_editor->m_builder.m_settings.m_framerate = std::stoi(framerate);
        ImGui::Separator();
        ImGui::Text("Cookable Scenes");



        for (int32 i = 0; i < SceneManager::Instance().m_scenes.size(); ++i)
        {
          ImGui::PushID(i);
          SharedPtr<Scene> item = SceneManager::Instance().m_scenes[i];
          ImGui::Text(Utils::Format("%d )", i).c_str());
          ImGui::SameLine();
          ImGui::Checkbox(Utils::Format("##CkbxScn_%s",
            item->m_sceneName.c_str()).c_str(),
            &m_windowVisibilities[Utils::Format("##CkbxScn_%s",
              item->m_sceneName.c_str())]);

          if (m_windowVisibilities[Utils::Format("##CkbxScn_%s", item->m_sceneName.c_str())])
          {
            Scene* toCook = SceneManager::Instance().FindScene(item->m_sceneName);
            App::Instance().m_editor->m_builder.m_settings.m_cookableScenes[i] = toCook;
          }
          else
          {
            App::Instance().m_editor->m_builder.m_settings.m_cookableScenes[i] = nullptr;
          }
          ImGui::SameLine();
          ImGui::Button(item->m_sceneName.c_str(),
            ImVec2(ImGui::GetWindowWidth() - ImGui::CalcItemWidth() / 2,
              ImGui::GetFrameHeight()));

          // Our buttons are both drag sources and drag targets here!
          if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
          {
            // Set payload to carry the index of our item (could be anything)
            ImGui::SetDragDropPayload("PROJECTSCENES", &i, sizeof(int));

            // Display preview (could be anything, e.g. when dragging an image we could decide to display
            // the filename and a small preview of the image, etc.)
            ImGui::Text("Reorder %s", item->m_sceneName.c_str());
            ImGui::EndDragDropSource();
          }
          if (ImGui::BeginDragDropTarget())
          {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("PROJECTSCENES"))
            {
              IM_ASSERT(payload->DataSize == sizeof(int));
              int payload_n = *(const int*)payload->Data;

              std::swap(SceneManager::Instance().m_scenes[payload_n], SceneManager::Instance().m_scenes[i]);

            }
            ImGui::EndDragDropTarget();
          }
          ImGui::PopID();

        }

        ImGui::Separator();

        ImGui::Separator();


        // Hit that motherfucking button
        if (ImGui::Button("Build Project"))
        {
          IGFD::FileDialogConfig config;
          config.path = ".";
          ImGuiFileDialog::Instance()->OpenDialog("ChooseDirDlgKey", "Choose a Directory", nullptr, config);
        }


        ImGui::End();
      }

      if (m_windowVisibilities["EntityInspector"])
      {
        if (ImGui::Begin("Entity Inspector"))
        {
          for (auto& e : App::Instance().m_editor->m_controller.m_selectedEntities)
          {
            String n = e->GetName();
            ImGui::Text("EntityName");
            ImGui::SameLine();
            if (ImGui::InputText("##entityName", &n[0], ImGuiInputTextFlags_EnterReturnsTrue))
            {
              e->SetName(n);
            }
            ImGui::Text("Transform");
            ImGui::Separator();
            ImGui::Text("Position");
            Vector2f pos = e->GetTransform().position;
            ImGui::Text("X: ");
            ImGui::SameLine();
            ImGui::PushItemWidth(ImGui::GetWindowSize().x / 4);
            ImGui::DragFloat("##entityX", &pos.x, 0.05f, -1000000.0f, +1000000.0f, "%.3f");
            ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::Text("Y: ");
            ImGui::SameLine();
            ImGui::PushItemWidth(ImGui::GetWindowSize().x / 4);
            ImGui::DragFloat("##entityY", &pos.y, 0.05f, -1000000.0f, +1000000.0f, "%.3f");
            ImGui::PopItemWidth();
            e->SetPosition(pos);

            // Components
            if (e->GetComponent<Animator>() != nullptr)
            {
              ImGui::Separator();
              ImGui::Text("Animator");
              for (auto& animation : e->GetComponent<Animator>()->m_animations)
              {
                ImGui::Text(animation.first.c_str());
              }
            }
            if (e->GetComponent<Sprite>() != nullptr)
            {
              ImGui::Separator();
              ImGui::Text("Sprite");
              ImGui::ImageButton("##entitySprite", 
                                 static_cast<sf::Sprite>(*e->GetComponent<Sprite>()), 
                                 Vector2f(ImGui::GetWindowSize().x / 2, 
                                          ImGui::GetWindowSize().x / 2));
            }
            // End Components
          }
        }
        ImGui::End();
      }

      if (m_windowVisibilities["Logger"])
      {
        if (ImGui::Begin("Logger"))
        {
          if (ImGui::Button("Clear"))
          {
            m_debugLogs.clear();
          }
          ImGui::SameLine();
          // TODO: Make Collapse be able to see the full log
          // TODO: Make Collapse also make a shorter version of the log
          ImGui::Button("Collapse");
          ImGui::SameLine();
          // TODO:: Add a Pause System
          ImGui::Button("ErrorPause");
          ImGui::SameLine();
          ImGui::Checkbox("Error", &m_windowVisibilities["errorCheckbox"]);
          ImGui::SameLine();
          ImGui::Checkbox("Warnings", &m_windowVisibilities["warningCheckbox"]);
          ImGui::SameLine();
          ImGui::Checkbox("Logs", &m_windowVisibilities["logCheckbox"]);
          ImGui::Spacing();
          ImGui::Separator();
          ImGui::Spacing();

          ImGui::BeginChild("LogsArea", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
          for (const auto& log : m_debugLogs)
          {
            if (m_windowVisibilities["errorCheckbox"] && 
                log->m_warningLevel == eLOGLEVEL::ERROR)
            {
              ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 0, 0, 255));
              if (ImGui::Selectable(log->m_message.c_str(), &m_windowVisibilities["selectedLog"]))
              {
                // TODO: Add an extra string that you can see with more precision
              }
              ImGui::PopStyleColor();
            }
            else if (m_windowVisibilities["warningCheckbox"] && 
                     log->m_warningLevel == eLOGLEVEL::WARNING)
            {
              ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(255, 200, 0, 255));
              if (ImGui::Selectable(log->m_message.c_str(), &m_windowVisibilities["selectedLog"]))
              {
                // TODO: Add an extra string that you can see with more precision
              }
              ImGui::PopStyleColor();
            }
            else if (m_windowVisibilities["logCheckbox"] && 
                     log->m_warningLevel == eLOGLEVEL::DEFAULT)
            {
              if (ImGui::Selectable(log->m_message.c_str(), &m_windowVisibilities["selectedLog"]))
              {
                // TODO: Add an extra string that you can see with more precision
              }
            }
          }
          ImGui::EndChild();

        }
        ImGui::End();
      }

      if (m_windowVisibilities["Resources"])
      {
        if (ImGui::Begin("Resource Explorer"))
        {
          ImGui::Columns(2, "ResourcesColums");
          
          // Tree view
          ImGui::BeginChild("Explorer", ImVec2(0, 0));
          ImGui::Text("Explorer");
          ImGui::EndChild();
          ImGui::NextColumn();

          // Items
          
          assets_browser.Draw();
          
          
          ImGui::Columns(1);
        }
        ImGui::End();
      }

      if (m_windowVisibilities["SceneGraph"])
      {
        if (ImGui::Begin("Scene Graph"))
        {
          ImGui::Text(SceneManager::Instance().m_activeScene->m_sceneName.c_str());
          ImGui::Separator();
        }
        ImGui::End();
      }

      if (m_windowVisibilities["ViewportOptions"])
      {
        ImGui::OpenPopup("popup_viewport");
        m_windowVisibilities["ViewportOptions"] = false;
      }
      if (ImGui::BeginPopup("popup_viewport"))
      {
        ImGui::Text("Viewport options");
        if (ImGui::Button("Close"))
        {
          ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
      }

      if (ImGuiFileDialog::Instance()->Display("ChooseDirDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
          std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
          std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
          App::Instance().m_editor->m_builder.m_settings.m_projectDir = filePath;
          // action
          if (App::Instance().m_editor->m_builder.m_settings.m_projectName.empty())
          {
            App::Instance().m_editor->m_builder.m_settings.m_projectName = "UIGame";
          }
          m_windowVisibilities["buildingPopup"] = true;
          App::Instance().m_editor->m_builder.StartBuildingThread();
        }

        // close
        ImGuiFileDialog::Instance()->Close();
      }

      if (m_windowVisibilities["buildingPopup"])
      {
        ImVec2 pos = ImGui::GetIO().DisplaySize;
        ImVec2 nextSize(pos.x / 7, pos.y / 7);
        pos.x = pos.x / 2 - nextSize.x / 2;
        pos.y = pos.y / 2 - nextSize.y / 2;
        ImGui::SetNextWindowPos(pos);
        ImGui::SetNextWindowSize(nextSize);
        ImGui::OpenPopup("building_popup");
      }
      if (ImGui::BeginPopup("building_popup"))
      {
        ImGui::Text("Building...");
        ImGui::Separator();
        if (App::Instance().m_editor->m_builder.m_buildingPercentage < 100)
        {
          ImSpinner::SpinnerFadeDots("Building",
            ImSpinner::Radius(16),
            ImSpinner::Thickness(6),
            ImSpinner::Color(ImColor(255, 255, 255, 255)),
            ImSpinner::Speed(10));
          ImGui::Text(Utils::Format("%2f",
            App::Instance().m_editor->m_builder.m_buildingPercentage).c_str());
          ImGui::Separator();
        }
        else if (App::Instance().m_editor->m_builder.m_buildingPercentage == 100)
        {
          if (ImGui::Button("Build Completed"))
          {
            m_windowVisibilities["buildingPopup"] = false;
            ImGui::CloseCurrentPopup();
          }
        }
        // App::Instance().m_projectBuilder->BuildProject();
        ImGui::EndPopup();
      }

      if (m_windowVisibilities["iconPopup"])
      {
        ImGui::OpenPopup("icon_options");
        m_windowVisibilities["iconPopup"] = false;
      }
      if (ImGui::BeginPopup("icon_options"))
      {
        ImGui::Text("Set Image");
        ImGui::Separator();

        Map<SizeT, SharedPtr<Resource>>::iterator res;
        for (res = ResourceManager::Instance().m_resources.begin();
          res != ResourceManager::Instance().m_resources.end();
          ++res)
        {
          if (res->second->GetType() == eRESOURCETYPE::TEXTURE)
          {
            if (ImGui::Selectable(res->second->m_resName.c_str()))
            {
              App::Instance().m_editor->m_builder.m_projectIconStr = res->second->m_resName;
            }
          }
          // if (ResourceManager::Instance().GetResource<Texture>(res->second->m_resName) != nullptr)
          // {
          //   if (ImGui::Selectable(res->second->m_resName.c_str()))
          //   {
          //     App::Instance().m_projectBuilder->m_projectIconStr = res->second->m_resName;
          //   }
          // }
        }

        ImGui::EndPopup();
      }



      ImGuiDockNode* centralNode = ImGui::DockBuilderGetNode(ImGui::GetID("MainDock##2"));
      App::Instance().m_editor->m_camera.m_centralNode = centralNode;
      ImVec2 centralNodeSize = centralNode->CentralNode->Size;
      ImVec2 centralNodeStartPos = centralNode->CentralNode->Pos;
      float menuBarSize = ImGui::GetFrameHeight();  // Get height of menu bar
      ImGui::SetNextWindowPos(ImVec2(centralNodeStartPos.x, menuBarSize));

      // Set the bar to be the full width of the window, but with a small fixed height
      ImGui::SetNextWindowSize(ImVec2(centralNodeSize.x, menuBarSize));

      ImGui::Begin("##CameraInformation",
        nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoDocking);

      ImGui::Text("Camera Position");
      ImGui::SameLine();
      ImGui::Text(Utils::Format("X: %f --- Y: %f",
        App::Instance().m_editor->m_camera.GetTransform().position.x,
        App::Instance().m_editor->m_camera.GetTransform().position.y).c_str());

      ImGui::End();

      /************************************************************************/
      /*                                                                      */
      /************************************************************************/
      // Wtf was this supposed to do?
      // ImGui::SetNextWindowSize(ImVec2(300, 150));
      // ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2) );


    }


    ImGui::End();


  }
}
