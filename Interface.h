#pragma once
#include "Configuration.hpp"
#include "dropboxes.h"
#include "Variables.h"
#include <cctype>
#include "Listener.h"
#include "SpecList.h"
#include "namespammer.h"
#include "Radar.h"
#include "memoryfonts.h"
#include "SkinParser.h"
#include "SkinFilter.h"
#include <vector>

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
#define BUILDSTAMP ( __DATE__ )


void FullUpdate()
{
	g_Engine->ClientCmd_Unrestricted("cl_fullupdate 1");
}

//========Clantag====================

void SetClantag(const char *tag)
{
	static auto fnClantagChanged = (int(__fastcall*)(const char*, const char*))U::pattern_scan(GetModuleHandle("engine.dll"), "53 56 57 8B DA 8B F9 FF 15");

	fnClantagChanged(tag, tag);
}
//--------------------------------------------
//Weapon CFG stuff

const char* weaponnames(int id)
{
	switch (id)
	{
	case 1:
		return "deagle";
	case 2:
		return "elite";
	case 3:
		return "fiveseven";
	case 4:
		return "glock";
	case 7:
		return "ak47";
	case 8:
		return "aug";
	case 9:
		return "awp";
	case 10:
		return "famas";
	case 11:
		return "g3sg1";
	case 13:
		return "galilar";
	case 14:
		return "m249";
	case 60:
		return "m4a1_silencer";
	case 16:
		return "m4a1";
	case 17:
		return "mac10";
	case 19:
		return "p90";
	case 24:
		return "ump45";
	case 25:
		return "xm1014";
	case 26:
		return "bizon";
	case 27:
		return "mag7";
	case 28:
		return "negev";
	case 29:
		return "sawedoff";
	case 30:
		return "tec9";
	case 32:
		return "hkp2000";
	case 33:
		return "mp7";
	case 34:
		return "mp9";
	case 35:
		return "nova";
	case 36:
		return "p250";
	case 38:
		return "scar20";
	case 39:
		return "sg556";
	case 40:
		return "ssg08";
	case 61:
		return "usp_silencer";
	case 63:
		return "cz75a";
	case 64:
		return "revolver";
	case 508:
		return "knife_m9_bayonet";
	case 500:
		return "bayonet";
	case 505:
		return "knife_flip";
	case 506:
		return "knife_gut";
	case 507:
		return "knife_karambit";
	case 509:
		return "knife_tactical";
	case 512:
		return "knife_falchion";
	case 514:
		return "knife_survival_bowie";
	case 515:
		return "knife_butterfly";
	case 516:
		return "knife_push";

	default:
		return "";
	}
}

bool IsUtility(ItemDefinitionIndexx index)
{
	switch (index)
	{
	case ItemDefinitionIndexx::ITEM_NONE:
	case ItemDefinitionIndexx::WEAPON_C4:
	case ItemDefinitionIndexx::WEAPON_FLASH:
	case ItemDefinitionIndexx::WEAPON_HE:
	case ItemDefinitionIndexx::WEAPON_INC:
	case ItemDefinitionIndexx::WEAPON_MOLOTOV:
	case ItemDefinitionIndexx::WEAPON_SMOKE:
	case ItemDefinitionIndexx::WEAPON_DECOY:
	case ItemDefinitionIndexx::WEAPON_TASER:
	case ItemDefinitionIndexx::WEAPON_KNIFE_T:
	case ItemDefinitionIndexx::WEAPON_KNIFE_CT:
	case ItemDefinitionIndexx::GLOVE_T_SIDE:
	case ItemDefinitionIndexx::GLOVE_CT_SIDE:
	case ItemDefinitionIndexx::GLOVE_SPORTY:
	case ItemDefinitionIndexx::GLOVE_SLICK:
	case ItemDefinitionIndexx::GLOVE_LEATHER_WRAP:
	case ItemDefinitionIndexx::GLOVE_STUDDED_BLOODHOUND:
	case ItemDefinitionIndexx::GLOVE_MOTORCYCLE:
	case ItemDefinitionIndexx::GLOVE_SPECIALIST:
	case ItemDefinitionIndexx::GLOVE_HYDRA:
		return true;
	default:
		return false;
	}
}

bool Contains(const std::string &word, const std::string &sentence) {
	if (word == "" || sentence == "")
		return true;

	return sentence.find(word) != std::string::npos;
}

std::string ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), (int(*)(int))std::tolower);

	return str;
}
//--------------------------------------------
bool defaultk;
bool bayonet;
bool flip;
bool gut;
bool karambit;
bool m9bayonet;
bool huntsman;
bool falchion;
bool bowie;
bool butterfly;
bool daggers;

void doknives(bool* disknife)
{
	defaultk = false;
	bayonet = false;
	flip = false;
	gut = false;
	karambit = false;
	m9bayonet = false;
	huntsman = false;
	falchion = false;
	bowie = false;
	butterfly = false;
	daggers = false;

	*disknife = true;
}

const char* HitmarkSound[] =
{
	"Disabled",
	"Default",
	"Roblox",
	"Trump",
	"Metallic"
};


void orginalbuttons()
{
	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Button] = ImColor(21, 21, 21, 255);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(21, 21, 21, 255);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(21, 21, 21, 255);
}


void btndefault()
{
	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Button] = ImColor(255, 0, 0, 255);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(255, 0, 0, 255);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(255, 0, 0, 255);
}



void bordernew()
{
	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, .27f, 1.00f);
}



void orginalchild()
{
	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);
	style.ChildRounding = 0.0f;
}

int ParseSkins()
{
	valve_parser::Document doc;
	auto r = doc.Load(".\\csgo\\scripts\\items\\items_game.txt", valve_parser::ENCODING::UTF8);
	if (!r)
		return 1;

	valve_parser::Document english;
	r = english.Load(".\\csgo\\resource\\csgo_english.txt", valve_parser::ENCODING::UTF16_LE);
	if (!r)
		return 2;

	auto weaponSkinCombo = doc.BreadthFirstSearch("weapon_icons");
	if (!weaponSkinCombo || !weaponSkinCombo->ToObject())
		return 3;

	auto skinDataVec = doc.BreadthFirstSearchMultiple("paint_kits");
	if (!skinDataVec.size())
		return 4;

	auto PaintKitNames = english.BreadthFirstSearch("Tokens");
	if (!PaintKitNames || !PaintKitNames->ToObject())
		return 5;

	//std::unordered_map<std::string, std::set<std::string>> G::weaponSkins;
	//std::unordered_map<std::string, skinInfo> G::skinMap;
	//std::unordered_map<std::string, std::string> G::skinNames;

	std::vector<std::string> weaponNames = {
		"deagle",
		"elite",
		"fiveseven",
		"glock",
		"ak47",
		"aug",
		"awp",
		"famas",
		"g3sg1",
		"galilar",
		"m249",
		"m4a1_silencer", //needs to be before m4a1 else silencer doesnt get filtered out :D
		"m4a1",
		"mac10",
		"p90",
		"ump45",
		"xm1014",
		"bizon",
		"mag7",
		"negev",
		"sawedoff",
		"tec9",
		"hkp2000",
		"mp7",
		"mp9",
		"nova",
		"p250",
		"scar20",
		"sg556",
		"ssg08",
		"usp_silencer",
		"cz75a",
		"revolver",
		"knife_m9_bayonet", //needs to be before bayonet else knife_m9_bayonet doesnt get filtered out :D
		"bayonet",
		"knife_flip",
		"knife_gut",
		"knife_karambit",
		"knife_tactical",
		"knife_falchion",
		"knife_survival_bowie",
		"knife_butterfly",
		"knife_push",
		"studded_bloodhound_gloves",
		"sporty_gloves",
		"slick_gloves",
		"leather_handwraps",
		"motorcycle_gloves",
		"specialist_gloves"

	};

	//populate G::weaponSkins
	for (auto child : weaponSkinCombo->children)
	{
		if (child->ToObject())
		{
			for (auto weapon : weaponNames)
			{
				auto skinName = child->ToObject()->GetKeyByName("icon_path")->ToKeyValue()->Value.toString();
				auto pos = skinName.find(weapon);
				//filter out the skinname
				if (pos != std::string::npos)
				{
					auto pos2 = skinName.find_last_of('_');
					g_Options.Skinchanger.weaponSkins[weapon].insert(
						skinName.substr(pos + weapon.length() + 1,
							pos2 - pos - weapon.length() - 1)
					);
					break;
				}
			}
		}
	}

	//populate skinData
	for (auto skinData : skinDataVec)
	{
		if (skinData->ToObject())
		{
			for (auto skin : skinData->children)
			{
				if (skin->ToObject())
				{
					skinInfo si;
					si.paintkit = skin->ToObject()->name.toInt();

					auto skinName = skin->ToObject()->GetKeyByName("name")->ToKeyValue()->Value.toString();
					auto tagNode = skin->ToObject()->GetKeyByName("description_tag");
					if (tagNode)
					{
						std::string tag = tagNode->ToKeyValue()->Value.toString();
						tag = tag.substr(1, std::string::npos); //skip #
						std::transform(tag.begin(), tag.end(), tag.begin(), towlower);
						si.tagName = tag;
					}

					auto keyVal = skin->ToObject()->GetKeyByName("seed");
					if (keyVal != nullptr)
						si.seed = keyVal->ToKeyValue()->Value.toInt();

					g_Options.Skinchanger.skinMap[skinName] = si;
				}
			}
		}
	}

	//populate G::skinNames
	for (auto child : PaintKitNames->children)
	{
		if (child->ToKeyValue())
		{
			std::string key = child->ToKeyValue()->Key.toString();
			std::transform(key.begin(), key.end(), key.begin(), towlower);
			if (key.find("paintkit") != std::string::npos &&
				key.find("tag") != std::string::npos)
			{
				g_Options.Skinchanger.skinNames[key] = child->ToKeyValue()->Value.toString();
			}
		}
	}

	return 0;
}



void initializeskins()
{
	static bool once = false;

	if (!once)
	{
		ParseSkins();
		once = true;
	}
}

namespace prometheus
{

	ImFont* fDefault;
	ImFont* fkek;
	ImFont* fkek2;

	void GUI_Init(HWND window, IDirect3DDevice9 *pDevice)
	{

		if (ImGui_ImplDX9_Init(window, pDevice))
		{

			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();

			fDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\SEGOEUI.ttf", 14.0f);
			fkek = io.Fonts->AddFontFromMemoryCompressedTTF(myfont4_compressed_data, myfont4_compressed_size, 42.f);
			fkek2 = io.Fonts->AddFontFromMemoryCompressedTTF(myfont3_compressed_data, myfont3_compressed_size, 30.f);


			auto& style = ImGui::GetStyle();

			style.Alpha = 1.0f;
			G::extra_flags = 0;
			style.WindowPadding = ImVec2(10, 10);
			style.WindowRounding = 5.0f;
			style.FramePadding = ImVec2(5, 5);
			style.FrameRounding = 0.0f;
			style.ItemSpacing = ImVec2(5, 5);
			style.ItemInnerSpacing = ImVec2(8, 6);
			style.IndentSpacing = 25.0f;
			style.ScrollbarSize = 15.0f;
			style.ScrollbarRounding = 9.0f;
			style.GrabMinSize = 10.0f;
			style.GrabRounding = 0.0f;


			style.Colors[ImGuiCol_Text] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
			style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.78f);
			style.Colors[ImGuiCol_WindowBg] = ImColor(15, 15, 15, 255);
			style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);
			style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.09f);
			style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.04f, 0.04f, 0.04f, 0.88f);
			style.Colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
			style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 0.75f);
			style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
			style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
			style.Colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0, 0);
			style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(66, 66, 66, 255);
			style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(66, 66, 66, 255);
			style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(66, 66, 66, 255);
			style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.60f, 0.78f, 1.00f);
			style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
			style.Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.00f, 0.00f, 0.83f);
			style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			style.Colors[ImGuiCol_Button] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
			style.Colors[ImGuiCol_Header] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
			style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
			style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
			style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.70f, 0.02f, 0.60f, 0.22f);


			style.Colors[ImGuiCol_Button1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_Button2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_Button3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_Button4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_Button5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_Button6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonHovered6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
			style.Colors[ImGuiCol_ButtonActive6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

			G::d3dinit = true;
		}

	}

	void rendernewbutton1()
	{
		auto& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Button1] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered1] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive1] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

		style.Colors[ImGuiCol_Button2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);


		style.Colors[ImGuiCol_Button4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);


		style.Colors[ImGuiCol_Button5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

	}

	void rendernewbutton2()
	{
		auto& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Button2] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered2] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive2] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

		style.Colors[ImGuiCol_Button1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	}

	void rendernewbutton3()
	{
		auto& style = ImGui::GetStyle();


		style.Colors[ImGuiCol_Button3] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered3] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive3] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);


		style.Colors[ImGuiCol_Button1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	}

	void rendernewbutton4()
	{
		auto& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Button4] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered4] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive4] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

		style.Colors[ImGuiCol_Button1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);


		style.Colors[ImGuiCol_Button5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	}

	void rendernewbutton5()
	{
		auto& style = ImGui::GetStyle();


		style.Colors[ImGuiCol_Button5] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered5] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive5] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

		style.Colors[ImGuiCol_Button1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);


		style.Colors[ImGuiCol_Button4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive6] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	}

	void rendernewbutton6()
	{
		auto& style = ImGui::GetStyle();


		style.Colors[ImGuiCol_Button6] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered6] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive6] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);

		style.Colors[ImGuiCol_Button1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive1] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive2] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

		style.Colors[ImGuiCol_Button3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive3] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);


		style.Colors[ImGuiCol_Button4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive4] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);


		style.Colors[ImGuiCol_Button5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive5] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

	}




	void mainWindow()
	{

		C_BaseEntity* local;

		auto& style = ImGui::GetStyle();
		static int page = 1;

		ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(850.f, 580.f));

		if (ImGui::Begin("", &g_Options.Menu.Opened, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar));
		{

			bordernew();

			ImGui::BeginChild("#buttonstabs", ImVec2(830, 70), true, ImGuiWindowFlags_NoScrollbar);
			{

				ImGui::PushFont(fkek);
				if (ImGui::Button1("r", ImVec2(127.1667f, 50.0f))) //Ragebot
				{
					page = 1;
					rendernewbutton1();
				}
				ImGui::SameLine(0.0, 8.0f);
				if (ImGui::Button2("l", ImVec2(127.1667f, 50.0f)))//Legitbot
				{
					page = 2;
					rendernewbutton2();
				}
				ImGui::SameLine(0.0, 8.0f);
				if (ImGui::Button3("V", ImVec2(127.1667f, 50.0f)))//Visuals
				{
					page = 3;
					rendernewbutton3();
				}
				ImGui::SameLine(0.0, 8.0f);
				if (ImGui::Button4("c", ImVec2(127.1667f, 50.0f)))//Colors
				{
					page = 4;
					rendernewbutton4();
				}
				ImGui::SameLine(0.0, 8.0f);
				if (ImGui::Button5("s", ImVec2(127.1667f, 50.0f)))//Skinchanger
				{
					page = 5;
					rendernewbutton5();

				}
				ImGui::SameLine(0.0, 8.0f);
				if (ImGui::Button6("M", ImVec2(127.1667f, 50.0f)))//Misc
				{
					page = 6;

					rendernewbutton6();
				}
				ImGui::PopFont();

			}ImGui::EndChild();

			if (page == 1)
			{
				orginalchild();
				orginalbuttons();

				static int ragepage = 0;

				if (ImGui::Button(("RAGE-General"), ImVec2(270.0f, 30.0f)))
				{
					ragepage = 0;
				}

				ImGui::SameLine();


				if (ImGui::Button(("RAGE-Resolver"), ImVec2(270.0f, 30.0f)))
				{
					ragepage = 1;
				}

				ImGui::SameLine();

				if (ImGui::Button(("RAGE-AntiAim"), ImVec2(270.0f, 30.0f)))
				{
					ragepage = 2;
				}


				ImGui::Separator();

				ImGui::Spacing();


				if (ragepage == 0)
				{
					btndefault();
					ImGui::BeginChild("#ragechild1", ImVec2(260, 350), true);
					{

						ImGui::Text(("Aimbot-General"));
						ImGui::Separator();
						ImGui::Checkbox(("Active"), &g_Options.Ragebot.MainSwitch);
						ImGui::Checkbox(("Enabled"), &g_Options.Ragebot.Enabled);
						ImGui::Checkbox(("Auto Fire"), &g_Options.Ragebot.AutoFire);
						ImGui::PushItemWidth(180);
						ImGui::SliderFloat(("FOV"), &g_Options.Ragebot.FOV, 1.f, 180.f, "%.0f");
						ImGui::PopItemWidth();
						ImGui::PushItemWidth(180);
						ImGui::Hotkey(("##Ragebot-Key"), &g_Options.Ragebot.KeyPress, ImVec2(150, 25));
						ImGui::SameLine();
						ImGui::Text("Key");
						ImGui::PopItemWidth();
						ImGui::Checkbox(("Silent Aim"), &g_Options.Ragebot.Silent);
						ImGui::Checkbox(("Auto Pistol"), &g_Options.Ragebot.AutoPistol);


						ImGui::Hotkey(("Flip Key##FlipKey"), &g_Options.Ragebot.flipkey, ImVec2(125, 25));

						ImGui::Checkbox(("Fakelag"), &g_Options.Ragebot.FakeLag);
						ImGui::Combo(("Type"), &g_Options.Ragebot.FakeLagMode, fakelag, ARRAYSIZE(fakelag));
						ImGui::SliderInt(("##Fakelag"), &g_Options.Ragebot.FakeLagAmt, 1.f, 15.f);


					}ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("#ragechild2", ImVec2(270, 350), true);
					{

						ImGui::Checkbox(("No Recoil"), &g_Options.Ragebot.AntiRecoil);
						ImGui::Combo(("Auto Stop"), &g_Options.Ragebot.AutoStop, autostop, ARRAYSIZE(autostop));
						ImGui::Checkbox(("Auto Crouch"), &g_Options.Ragebot.AutoCrouch);
						ImGui::Checkbox(("Auto Scope"), &g_Options.Ragebot.AutoScope);
						ImGui::Checkbox(("Fakewalk"), &g_Options.Ragebot.fakewalk);
						ImGui::Hotkey(("##fakewalk key"), &g_Options.Ragebot.fakewalkkey, ImVec2(125, 25));
						ImGui::Separator();
						ImGui::PushItemWidth(120);
						ImGui::Text("Minimal Damage");
						ImGui::Separator();
						ImGui::SliderFloat(("Snipers"), &g_Options.Ragebot.MinimumDamageSniper, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Rifles"), &g_Options.Ragebot.MinimumDamageRifle, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Pistols"), &g_Options.Ragebot.MinimumDamagePistol, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Heavies"), &g_Options.Ragebot.MinimumDamageHeavy, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("SMGs"), &g_Options.Ragebot.MinimumDamageSmg, 1.f, 100.f, "%.2f");
						ImGui::SliderFloat(("Revolver/Deagle"), &g_Options.Ragebot.MinimumDamageRevolver, 1.f, 100.f, "%.2f");
						ImGui::PopItemWidth();

					}ImGui::EndChild();



					ImGui::SameLine();

					ImGui::BeginChild("#ragechild3", ImVec2(260, 350), true);
					{
						ImGui::Text(("Aimbot-Accuracy"));
						ImGui::Separator();
						ImGui::Checkbox(("Friendly Fire"), &g_Options.Ragebot.FriendlyFire);
						ImGui::PushItemWidth(130);
						ImGui::Combo(("Hitbox"), &g_Options.Ragebot.Hitbox, aimBones, ARRAYSIZE(aimBones));
						ImGui::Combo(("Hitscan"), &g_Options.Ragebot.Hitscan, hitscan, ARRAYSIZE(hitscan));
						ImGui::PopItemWidth();
						ImGui::Separator();
						ImGui::PushItemWidth(120);
						ImGui::Checkbox(("Hitchance Enabled"), &g_Options.Ragebot.Hitchance);
						ImGui::SliderFloat(("Snipers"), &g_Options.Ragebot.HitchanceSniper, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(("Rifles"), &g_Options.Ragebot.HitchanceRifle, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(("Pistols"), &g_Options.Ragebot.HitchancePistol, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(("SMGs"), &g_Options.Ragebot.HitchanceSmgs, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(("Heavies"), &g_Options.Ragebot.HitchanceHeavy, 0.f, 100.f, "%.1f");
						ImGui::SliderFloat(("Revolver / Deagle"), &g_Options.Ragebot.HitchanceRevolver, 0.f, 100.f, "%.1f");
						ImGui::PopItemWidth();
					}ImGui::EndChild();


				}


				if (ragepage == 1)
				{
					ImGui::BeginChild("#ragechild4", ImVec2(330, 300), true);
					{
						btndefault();
						ImGui::PushItemWidth(110);
						ImGui::Combo(("Resolver"), &g_Options.Ragebot.Resolver, resolvers, ARRAYSIZE(resolvers));
						ImGui::Text(("Bruteforce after X bullets:"));
						ImGui::SliderFloat(("Shots: "), &g_Options.Ragebot.bruteAfterX, 0, 10, "%1.f");
						ImGui::Checkbox(("Fakelag Fix"), &g_Options.Ragebot.FakeLagFix);
						ImGui::Checkbox(("Position Adjustment"), &g_Options.Ragebot.PosAdjust);
						ImGui::Hotkey(("##BAIMkey"), &g_Options.Ragebot.BAIMkey, ImVec2(150, 25));
						ImGui::SameLine();
						ImGui::Text("BAIMkey");
						ImGui::Checkbox(("BAIM If Lethal"), &g_Options.Ragebot.BAIMIfLethal);

						ImGui::PopItemWidth();

					}ImGui::EndChild();
				}


				if (ragepage == 2)
				{
					static int antiaimpages = 0;

					ImGui::Checkbox(("Anti-Aim Enabled"), &g_Options.Ragebot.EnabledAntiAim);

					ImGui::Checkbox(("Edge"), &g_Options.Ragebot.Edge);
					ImGui::Checkbox(("AntiAim on knife"), &g_Options.Ragebot.KnifeAA);

					ImGui::BeginChild("##aa's", ImVec2(310.f, 288.f));
					{
						static int movementtype = 0;

						if (ImGui::Button("Run", ImVec2(55, 25)))
							movementtype = 0;
						ImGui::SameLine();
						if (ImGui::Button("Walk", ImVec2(55, 25)))
							movementtype = 1;
						ImGui::SameLine();
						if (ImGui::Button("Stand", ImVec2(55, 25)))
							movementtype = 2;
						ImGui::SameLine();
						if (ImGui::Button("Fake", ImVec2(55, 25)))
							movementtype = 3;
						ImGui::SameLine();
						if (ImGui::Button("Crouch", ImVec2(55, 25)))
							movementtype = 4;

						static int aatabtype = 0;
						static int aatabtype1 = 0;
						static int aatabtype2 = 0;
						static int aatabtype3 = 0;
						static int aatabtype4 = 0;

						switch (movementtype)
						{
						case 0:
						{
							ImGui::Checkbox(("AA On Run"), &g_Options.Ragebot.AA_onRun);


							if (ImGui::Button("Presets", ImVec2(150, 25))) aatabtype = 0;
							ImGui::SameLine();
							if (ImGui::Button("Self Made", ImVec2(150, 25))) aatabtype = 1;

							if (aatabtype == 0) //run_
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.run_PreAAs);
								ImGui::Combo(("Pitch"), &g_Options.Ragebot.run_Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
								ImGui::SliderFloat(("Pitch Adder: "), &g_Options.Ragebot.run_PitchAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Yaw"), &g_Options.Ragebot.run_YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
								ImGui::SliderFloat(("Real Adder: "), &g_Options.Ragebot.run_YawTrueAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Fake-Yaw"), &g_Options.Ragebot.run_YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
								ImGui::SliderFloat(("Fake Adder: "), &g_Options.Ragebot.run_YawFakeAdder, -180, 180, "%1.f");
							}
							else if (aatabtype == 1)
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.run_BuilderAAs);
								ImGui::SliderFloat(("Pitch Angle: "), &g_Options.Ragebot.run_BuilderPitch, -89, 89, "%1.f");
								ImGui::SliderFloat(("Real Angle: "), &g_Options.Ragebot.run_BuilderReal, -180, 180, "%1.f");
								ImGui::SliderFloat(("Fake Angle: "), &g_Options.Ragebot.run_BuilderFake, -180, 180, "%1.f");
								ImGui::Checkbox(("Enable Real Jitter"), &g_Options.Ragebot.run_Jitter);
								ImGui::SliderFloat(("Jitter Range: "), &g_Options.Ragebot.run_JitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("Enable Fake Jitter"), &g_Options.Ragebot.run_FJitter);
								ImGui::SliderFloat(("FJitter Range: "), &g_Options.Ragebot.run_FJitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("LBY Breaker"), &g_Options.Ragebot.run_LBYBreaker);
							}
							break;
						case 1:
							ImGui::Checkbox(("AA On Walk"), &g_Options.Ragebot.AA_onWalk);


							if (ImGui::Button("Presets", ImVec2(150, 25))) aatabtype1 = 0;
							ImGui::SameLine();
							if (ImGui::Button("Self Made", ImVec2(150, 25))) aatabtype1 = 1;

							if (aatabtype1 == 0) //walk_
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.walk_PreAAs);
								ImGui::Combo(("Pitch"), &g_Options.Ragebot.walk_Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
								ImGui::SliderFloat(("Pitch Adder: "), &g_Options.Ragebot.walk_PitchAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Yaw"), &g_Options.Ragebot.walk_YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
								ImGui::SliderFloat(("Real Adder: "), &g_Options.Ragebot.walk_YawTrueAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Fake-Yaw"), &g_Options.Ragebot.walk_YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
								ImGui::SliderFloat(("Fake Adder: "), &g_Options.Ragebot.walk_YawFakeAdder, -180, 180, "%1.f");
							}
							else if (aatabtype1 == 1)
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.walk_BuilderAAs);
								ImGui::SliderFloat(("Pitch Angle: "), &g_Options.Ragebot.walk_BuilderPitch, -89, 89, "%1.f");
								ImGui::SliderFloat(("Real Angle: "), &g_Options.Ragebot.walk_BuilderReal, -180, 180, "%1.f");
								ImGui::SliderFloat(("Fake Angle: "), &g_Options.Ragebot.walk_BuilderFake, -180, 180, "%1.f");
								ImGui::Checkbox(("Enable Real Jitter"), &g_Options.Ragebot.walk_Jitter);
								ImGui::SliderFloat(("Jitter Range: "), &g_Options.Ragebot.walk_JitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("Enable Fake Jitter"), &g_Options.Ragebot.walk_FJitter);
								ImGui::SliderFloat(("FJitter Range: "), &g_Options.Ragebot.walk_FJitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("LBY Breaker"), &g_Options.Ragebot.walk_LBYBreaker);
							}
							break;
						case 2:
							ImGui::Checkbox(("AA On Stand"), &g_Options.Ragebot.AA_onStand);



							if (ImGui::Button("Presets", ImVec2(150, 25))) aatabtype2 = 0;
							ImGui::SameLine();
							if (ImGui::Button("Self Made", ImVec2(150, 25))) aatabtype2 = 1;

							if (aatabtype2 == 0) //stand_
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.stand_PreAAs);
								ImGui::Combo(("Pitch"), &g_Options.Ragebot.stand_Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
								ImGui::SliderFloat(("Pitch Adder: "), &g_Options.Ragebot.stand_PitchAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Yaw"), &g_Options.Ragebot.stand_YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
								ImGui::SliderFloat(("Real Adder: "), &g_Options.Ragebot.stand_YawTrueAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Fake-Yaw"), &g_Options.Ragebot.stand_YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
								ImGui::SliderFloat(("Fake Adder: "), &g_Options.Ragebot.stand_YawFakeAdder, -180, 180, "%1.f");

							}
							else if (aatabtype2 == 1)
							{

								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.stand_BuilderAAs);
								ImGui::SliderFloat(("Pitch Angle: "), &g_Options.Ragebot.stand_BuilderPitch, -89, 89, "%1.f");
								ImGui::SliderFloat(("Real Angle: "), &g_Options.Ragebot.stand_BuilderReal, -180, 180, "%1.f");
								ImGui::SliderFloat(("Fake Angle: "), &g_Options.Ragebot.stand_BuilderFake, -180, 180, "%1.f");
								ImGui::Checkbox(("Enable Real Jitter"), &g_Options.Ragebot.stand_Jitter);
								ImGui::SliderFloat(("Jitter Range: "), &g_Options.Ragebot.stand_JitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("Enable Fake Jitter"), &g_Options.Ragebot.stand_FJitter);
								ImGui::SliderFloat(("FJitter Range: "), &g_Options.Ragebot.stand_FJitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("LBY Breaker"), &g_Options.Ragebot.stand_LBYBreaker);
							}
							break;
						case 3:
							ImGui::Checkbox(("AA On FakeWalk"), &g_Options.Ragebot.AA_onFakeWalk);



							if (ImGui::Button("Presets", ImVec2(150, 25))) aatabtype3 = 0;
							ImGui::SameLine();
							if (ImGui::Button("Self Made", ImVec2(150, 25))) aatabtype3 = 1;

							if (aatabtype3 == 0) //fwalk_
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.fwalk_PreAAs);
								ImGui::Combo(("Pitch"), &g_Options.Ragebot.fwalk_Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
								ImGui::SliderFloat(("Pitch Adder: "), &g_Options.Ragebot.fwalk_PitchAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Yaw"), &g_Options.Ragebot.fwalk_YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
								ImGui::SliderFloat(("Real Adder: "), &g_Options.Ragebot.fwalk_YawTrueAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Fake-Yaw"), &g_Options.Ragebot.fwalk_YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
								ImGui::SliderFloat(("Fake Adder: "), &g_Options.Ragebot.fwalk_YawFakeAdder, -180, 180, "%1.f");
							}
							else if (aatabtype3 == 1)
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.fwalk_BuilderAAs);
								ImGui::SliderFloat(("Pitch Angle: "), &g_Options.Ragebot.fwalk_BuilderPitch, -89, 89, "%1.f");
								ImGui::SliderFloat(("Real Angle: "), &g_Options.Ragebot.fwalk_BuilderReal, -180, 180, "%1.f");
								ImGui::SliderFloat(("Fake Angle: "), &g_Options.Ragebot.fwalk_BuilderFake, -180, 180, "%1.f");
								ImGui::Checkbox(("Enable Real Jitter"), &g_Options.Ragebot.fwalk_Jitter);
								ImGui::SliderFloat(("Jitter Range: "), &g_Options.Ragebot.fwalk_JitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("Enable Fake Jitter"), &g_Options.Ragebot.fwalk_FJitter);
								ImGui::SliderFloat(("FJitter Range: "), &g_Options.Ragebot.fwalk_FJitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("LBY Breaker"), &g_Options.Ragebot.fwalk_LBYBreaker);
							}
							break;
						case 4:
							ImGui::Checkbox(("AA On Crouch"), &g_Options.Ragebot.AA_onCrouch);



							if (ImGui::Button("Presets", ImVec2(150, 25))) aatabtype4 = 0;
							ImGui::SameLine();
							if (ImGui::Button("Self Made", ImVec2(150, 25))) aatabtype4 = 1;

							if (aatabtype4 == 0) //crouch_
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.crouch_PreAAs);
								ImGui::Combo(("Pitch"), &g_Options.Ragebot.crouch_Pitch, antiaimpitch, ARRAYSIZE(antiaimpitch));
								ImGui::SliderFloat(("Pitch Adder: "), &g_Options.Ragebot.crouch_PitchAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Yaw"), &g_Options.Ragebot.crouch_YawTrue, antiaimyawtrue, ARRAYSIZE(antiaimyawtrue));
								ImGui::SliderFloat(("Real Adder: "), &g_Options.Ragebot.crouch_YawTrueAdder, -180, 180, "%1.f");
								ImGui::Separator();
								ImGui::Combo(("Fake-Yaw"), &g_Options.Ragebot.crouch_YawFake, antiaimyawfake, ARRAYSIZE(antiaimyawfake));
								ImGui::SliderFloat(("Fake Adder: "), &g_Options.Ragebot.crouch_YawFakeAdder, -180, 180, "%1.f");
							}
							else if (aatabtype4 == 1)
							{
								ImGui::Checkbox(("Enable"), &g_Options.Ragebot.crouch_BuilderAAs);
								ImGui::SliderFloat(("Pitch Angle: "), &g_Options.Ragebot.crouch_BuilderPitch, -89, 89, "%1.f");
								ImGui::SliderFloat(("Real Angle: "), &g_Options.Ragebot.crouch_BuilderReal, -180, 180, "%1.f");
								ImGui::SliderFloat(("Fake Angle: "), &g_Options.Ragebot.crouch_BuilderFake, -180, 180, "%1.f");
								ImGui::Checkbox(("Enable Real Jitter"), &g_Options.Ragebot.crouch_Jitter);
								ImGui::SliderFloat(("Jitter Range: "), &g_Options.Ragebot.crouch_JitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("Enable Fake Jitter"), &g_Options.Ragebot.crouch_FJitter);
								ImGui::SliderFloat(("FJitter Range: "), &g_Options.Ragebot.crouch_FJitterRange, -90, 90, "%1.f");
								ImGui::Checkbox(("LBY Breaker"), &g_Options.Ragebot.crouch_LBYBreaker);
							}
							break;
						}

						}ImGui::EndChild();
					}
				}
			}


			if (page == 2)
			{
				orginalbuttons();
				orginalchild();

				static int pagesshit = 1;
				static int legitbotpages = 1;


				if (ImGui::Button("LEGIT-BOT", ImVec2(270.0f, 30.0f)))
				{
					legitbotpages = 1;
				}

				ImGui::SameLine();

				if (ImGui::Button("TRIGGER-BOT", ImVec2(270.0f, 30.0f)))
				{
					legitbotpages = 2;
				}

				ImGui::SameLine();

				if (ImGui::Button("MISC", ImVec2(270.0f, 30.0f)))
				{
					legitbotpages = 3;
				}

				ImGui::Separator();


				ImGui::Spacing();
				ImGui::Spacing();


				if (legitbotpages == 1)
				{


					ImGui::BeginChild("#weaponssets", ImVec2(815, 50), false, ImGuiWindowFlags_NoScrollbar);
					{

						ImGui::Spacing();

						ImGui::PushFont(fkek2);
						ImGui::SameLine(0.0, 5.0f);
						if (ImGui::Button("W", ImVec2(157, 50)))
						{
							pagesshit = 1;
						}

						ImGui::SameLine(0.0, 5.0f);

						if (ImGui::Button("A", ImVec2(157, 50)))
						{
							pagesshit = 2;
						}
						ImGui::SameLine(0.0, 5.0f);
						if (ImGui::Button("Z", ImVec2(157, 50)))
						{
							pagesshit = 3;
						}
						ImGui::SameLine(0.0, 5.0f);
						if (ImGui::Button("N", ImVec2(157, 50)))
						{
							pagesshit = 4;
						}
						ImGui::SameLine(0.0, 5.0f);
						if (ImGui::Button("d", ImVec2(157, 50)))
						{
							pagesshit = 5;
						}
						ImGui::PopFont();



					}ImGui::EndChild();


					ImGui::Spacing();


					ImGui::Checkbox(("ENABLE"), &g_Options.LegitBot.Enable);

					ImGui::SameLine();

					ImGui::Checkbox(("Auto Pistol"), &g_Options.LegitBot.AutoPistol);


					if (pagesshit == 1)
					{

						ImGui::BeginChild("#Child1", ImVec2(400, 270), true);
						{
							btndefault();
							ImGui::PushItemWidth(300);

							ImGui::Text("RIFLES");

							ImGui::Separator();

							ImGui::Spacing();

							ImGui::Hotkey(("##mainkeyKEY"), &g_Options.LegitBot.MainKey, ImVec2(300, 25));
							ImGui::SameLine();
							ImGui::Text("Key");


							ImGui::Spacing();

							ImGui::SliderFloat(("SMOOTH"), &g_Options.LegitBot.MainSmooth, 1.00f, 100.00f, "%.2f");

							ImGui::Spacing();

							ImGui::SliderFloat(("FOV"), &g_Options.LegitBot.Mainfov, 0.00f, 30.00f, "%.2f");





						}ImGui::EndChild();


						ImGui::SameLine(0.0, 15.0f);


						ImGui::BeginChild("##Hiboxes", ImVec2(400, 270), true);
						{
							ImGui::Text("Hitbox");

							ImGui::Separator();

							ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 5));
							{
								ImGui::Selectable((" Head"), &g_Options.LegitBot.FilterMainWeapons.Headwpmain);
								ImGui::Selectable((" Neck"), &g_Options.LegitBot.FilterMainWeapons.Neckwpmain);
								ImGui::Selectable((" Chest"), &g_Options.LegitBot.FilterMainWeapons.Chestwpmain);
								ImGui::Selectable((" Stomach"), &g_Options.LegitBot.FilterMainWeapons.Stomachwpmain);
								ImGui::Selectable((" Multi-Bone"), &g_Options.LegitBot.FilterMainWeapons.multiboneswpmain);
							}ImGui::EndChild();

						}ImGui::EndChild();

					}

					if (pagesshit == 2)
					{

						ImGui::BeginChild("#Child2", ImVec2(400, 270), true);
						{
							btndefault();

							ImGui::Text("PISTOLS");

							ImGui::Separator();

							ImGui::Spacing();


							ImGui::PushItemWidth(300);

							ImGui::Hotkey(("##pistolKEY"), &g_Options.LegitBot.PistolKey, ImVec2(300, 25));
							ImGui::SameLine();
							ImGui::Text("Key");

							ImGui::Spacing();

							ImGui::SliderFloat(("SMOOTH"), &g_Options.LegitBot.PistolSmooth, 1.00f, 100.00f, "%.2f");

							ImGui::Spacing();

							ImGui::SliderFloat(("FOV"), &g_Options.LegitBot.Pistolfov, 0.00f, 30.00f, "%.2f");


						}ImGui::EndChild();


						ImGui::SameLine(0.0, 15.0f);

						ImGui::BeginChild("##Hiboxes2", ImVec2(400, 270), true);
						{
							btndefault();

							ImGui::Text("Hitbox");

							ImGui::Separator();

							ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 5));
							{
								ImGui::Selectable((" Head"), &g_Options.LegitBot.FilterPistolWeapons.Headwppis);
								ImGui::Selectable((" Neck"), &g_Options.LegitBot.FilterPistolWeapons.Neckwppis);
								ImGui::Selectable((" Chest"), &g_Options.LegitBot.FilterPistolWeapons.Chestwppis);
								ImGui::Selectable((" Stomach"), &g_Options.LegitBot.FilterPistolWeapons.Stomachwppis);
								ImGui::Selectable((" Multi-Bone"), &g_Options.LegitBot.FilterPistolWeapons.multiboneswppis);
							}ImGui::EndChild();


						}ImGui::EndChild();
					}

					if (pagesshit == 3)
					{
						ImGui::BeginChild("#Child3", ImVec2(400, 270), true);
						{
							btndefault();
							ImGui::Text("SNIPERS");

							ImGui::Separator();

							ImGui::Spacing();

							ImGui::PushItemWidth(300);

							ImGui::Hotkey(("##sniperkeyKEY"), &g_Options.LegitBot.SniperKey, ImVec2(300, 25));
							ImGui::SameLine();
							ImGui::Text("Key");

							ImGui::Spacing();

							ImGui::SliderFloat(("SMOOTH"), &g_Options.LegitBot.SniperSmooth, 1.00f, 100.00f, "%.2f");

							ImGui::Spacing();

							ImGui::SliderFloat(("FOV"), &g_Options.LegitBot.Sniperfov, 0.00f, 30.00f, "%.2f");

						}ImGui::EndChild();


						ImGui::SameLine(0.0, 15.0f);

						ImGui::BeginChild("##Hiboxes2", ImVec2(400, 270), true);
						{
							ImGui::Text("Hitbox");

							ImGui::Separator();


							ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 5));
							{
								ImGui::Selectable((" Head"), &g_Options.LegitBot.FilterSniperWeapons.HeadwpSnip);
								ImGui::Selectable((" Neck"), &g_Options.LegitBot.FilterSniperWeapons.NeckwpSnip);
								ImGui::Selectable((" Chest"), &g_Options.LegitBot.FilterSniperWeapons.ChestwpSnip);
								ImGui::Selectable((" Stomach"), &g_Options.LegitBot.FilterSniperWeapons.StomachwpSnip);
								ImGui::Selectable((" Multi-Bone"), &g_Options.LegitBot.FilterSniperWeapons.multiboneswpSnip);
							}ImGui::EndChild();


						}ImGui::EndChild();
					}

					if (pagesshit == 4)
					{

						ImGui::BeginChild("#Child4", ImVec2(400, 270), true);
						{
							btndefault();

							ImGui::Text("SMG");

							ImGui::Separator();

							ImGui::Spacing();

							ImGui::PushItemWidth(300);


							ImGui::Hotkey(("##smgKEY"), &g_Options.LegitBot.smg_Key, ImVec2(300, 25));
							ImGui::SameLine();
							ImGui::Text("Key");


							ImGui::Spacing();

							ImGui::SliderFloat(("SMOOTH"), &g_Options.LegitBot.smg_Smooth, 1.00f, 100.00f, "%.2f");

							ImGui::Spacing();

							ImGui::SliderFloat(("FOV"), &g_Options.LegitBot.smg_fov, 0.00f, 30.00f, "%.2f");


						}ImGui::EndChild();


						ImGui::SameLine(0.0, 15.0f);


						ImGui::BeginChild("##Hiboxes3", ImVec2(400, 270), true);
						{
							ImGui::Text("Hitbox");

							ImGui::Separator();

							ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 5));
							{
								ImGui::Selectable((" Head"), &g_Options.LegitBot.FiltersmgWeapons.Headwpsmg);
								ImGui::Selectable((" Neck"), &g_Options.LegitBot.FiltersmgWeapons.Neckwpsmg);
								ImGui::Selectable((" Chest"), &g_Options.LegitBot.FiltersmgWeapons.Chestwpsmg);
								ImGui::Selectable((" Stomach"), &g_Options.LegitBot.FiltersmgWeapons.Stomachwpsmg);
								ImGui::Selectable((" Multi-Bone"), &g_Options.LegitBot.FiltersmgWeapons.multiboneswpsmg);
							}ImGui::EndChild();

						}ImGui::EndChild();

					}

					if (pagesshit == 5)
					{
						ImGui::BeginChild("#Child5", ImVec2(400, 270), true);
						{
							btndefault();

							ImGui::Text("HEAVY");

							ImGui::Separator();

							ImGui::Spacing();

							ImGui::PushItemWidth(300);

							ImGui::Hotkey(("##heavyKEY"), &g_Options.LegitBot.heavy_wp_Key, ImVec2(300, 25));
							ImGui::SameLine();
							ImGui::Text("Key");


							ImGui::Spacing();

							ImGui::SliderFloat(("SMOOTH"), &g_Options.LegitBot.heavy_wp_Smooth, 1.00f, 100.00f, "%.2f");

							ImGui::Spacing();

							ImGui::SliderFloat(("FOV"), &g_Options.LegitBot.heavy_wp_fov, 0.00f, 30.00f, "%.2f");



						}ImGui::EndChild();


						ImGui::SameLine(0.0, 15.0f);


						ImGui::BeginChild("##Hiboxes4", ImVec2(400, 270), true);
						{
							ImGui::Text("Hitbox");

							ImGui::Separator();

							ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 5));
							{
								ImGui::Selectable((" Head"), &g_Options.LegitBot.FilterheavyWeapons.Headwphv);
								ImGui::Selectable((" Neck"), &g_Options.LegitBot.FilterheavyWeapons.Neckwphv);
								ImGui::Selectable((" Chest"), &g_Options.LegitBot.FilterheavyWeapons.Chestwphv);
								ImGui::Selectable((" Stomach"), &g_Options.LegitBot.FilterheavyWeapons.Stomachwphv);
								ImGui::Selectable((" Multi-Bone"), &g_Options.LegitBot.FilterheavyWeapons.multibonewphv);
							}ImGui::EndChild();


						}ImGui::EndChild();
					}



				}

				if (legitbotpages == 2)
				{

					ImGui::BeginChild("#triggerbot", ImVec2(400, 250), true);
					{
						btndefault();

						ImGui::Text(("TRIGGERBOT"));
						ImGui::Separator();

						ImGui::PushItemWidth(300);
						ImGui::Checkbox(("ENABLE-TRIGGERBOT"), &g_Options.LegitBot.Triggerbot.Enabled);


						ImGui::Hotkey("##triggerbotKey", &g_Options.LegitBot.Triggerbot.Key, ImVec2(300, 25));
						ImGui::SameLine();
						ImGui::Text("Key");


						ImGui::Spacing();

						ImGui::SliderFloat(("Delay"), &g_Options.LegitBot.Triggerbot.Delay, 1.f, 150.f, "%.0f");

						ImGui::Spacing();

						ImGui::SliderFloat(("Hitchance"), &g_Options.LegitBot.Triggerbot.hitchance, 1.f, 100.f, "%.0f");

						ImGui::PopItemWidth();
					}ImGui::EndChild();


					ImGui::SameLine(0.0, 15.0f);

					ImGui::BeginChild("#triggerbot2", ImVec2(400, 250), true);
					{
						ImGui::Text(("Filter"));
						ImGui::Separator();

						ImGui::BeginChild(("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 21 * 5));
						{
							ImGui::Selectable((" Head"), &g_Options.LegitBot.Triggerbot.Filter.Head);
							ImGui::Selectable((" Arms"), &g_Options.LegitBot.Triggerbot.Filter.Arms);
							ImGui::Selectable((" Chest"), &g_Options.LegitBot.Triggerbot.Filter.Chest);
							ImGui::Selectable((" Stomach"), &g_Options.LegitBot.Triggerbot.Filter.Stomach);
							ImGui::Selectable((" Legs"), &g_Options.LegitBot.Triggerbot.Filter.Legs);
						}ImGui::EndChild();
					} ImGui::EndChild();

				}

				if (legitbotpages == 3)
				{
					ImGui::BeginChild("BackTrack", ImVec2(400, 250), true);
					{
						ImGui::Checkbox(("Enable##backtrack"), &g_Options.Backtrack.backtrackenable);
						ImGui::PushItemWidth(110);
						ImGui::Combo((""), &g_Options.Backtrack.BacktrackType, Backtracktype, ARRAYSIZE(Backtracktype));
						ImGui::PopItemWidth();
						ImGui::PushItemWidth(180);
						ImGui::SliderInt("BackTrack - Ticks", &g_Options.Backtrack.backtrackticks, 1, 12);

						ImGui::PopItemWidth();
					}ImGui::EndChild();

				}
			}

			if (page == 3)
			{
				orginalchild();
				orginalbuttons();

				static int esppages = 0;

				ImGui::Checkbox(("ENABLE"), &g_Options.Visuals.Enabled);

				ImGui::SameLine();

				if (ImGui::Button("Visuals I", ImVec2(360.0f, 30.0f)))
				{
					esppages = 0;
				}

				ImGui::SameLine();

				if (ImGui::Button("Visuals II", ImVec2(360.0f, 30.0f)))
				{
					esppages = 1;
				}

				ImGui::Separator();
				ImGui::Spacing();

				if (esppages == 0)
				{


					btndefault();

					ImGui::BeginChild("##esppage1", ImVec2(270, 400), true);
					{
						if (ImGui::CollapsingHeader("Esp-General"))
						{
							ImGui::PushItemWidth(120);
							ImGui::Checkbox(("Box"), &g_Options.Visuals.Box);
							ImGui::SameLine();
							ImGui::PushItemWidth(110);
							ImGui::Combo("##boxkek", &g_Options.Visuals.BoxType, "Full\0\rCorners\0\r3D\0\0", -1);
							ImGui::Checkbox(("Team ESP"), &g_Options.Visuals.TeamESP);
							if (g_Options.Visuals.BoxType == 0)
							{
								ImGui::Checkbox(("Fill-Box"), &g_Options.Visuals.fill);
								ImGui::SliderFloat(("Alpha##alphafill"), &g_Options.Visuals.esp_fill_amount, 0.f, 255.f);
							}
							else if (g_Options.Visuals.BoxType == 1)
							{
								ImGui::Checkbox(("Fill-Box"), &g_Options.Visuals.fill);
								ImGui::SliderFloat(("Alpha##alphafill"), &g_Options.Visuals.esp_fill_amount, 0.f, 255.f);
							}
							else if (g_Options.Visuals.BoxType == 2)
							{
								g_Options.Visuals.fill = false;
								g_Options.Visuals.esp_fill_amount = 0.f;
							}
							ImGui::Checkbox(("Skeleton"), &g_Options.Visuals.skeletonenbl);
							ImGui::SameLine();
							ImGui::PushItemWidth(110);
							ImGui::Combo("##skelopts", &g_Options.Visuals.skeletonopts, skeletonopts, ARRAYSIZE(skeletonopts));
							ImGui::Checkbox(("Name"), &g_Options.Visuals.Name);
							ImGui::PushItemWidth(110);
							ImGui::Combo(("Weapon"), &g_Options.Visuals.Weapon, WeaponType, ARRAYSIZE(WeaponType));
							ImGui::Checkbox(("Aimlines"), &g_Options.Visuals.AimLine);
							ImGui::Checkbox(("Health##Enable"), &g_Options.Visuals.health);
							ImGui::SameLine();
							ImGui::PushItemWidth(110);
							ImGui::Combo(("Health##style"), &g_Options.Visuals.healthtype, healthtype, ARRAYSIZE(healthtype));
							ImGui::PopItemWidth();
							ImGui::Checkbox(("Armor Bar"), &g_Options.Visuals.armor);
							ImGui::Combo(("Armor"), &g_Options.Visuals.Armor2, armor, ARRAYSIZE(armor));
//							ImGui::Checkbox(("Ammo Box"), &g_Options.Visuals.AmmoBox);
						}


						if (ImGui::CollapsingHeader("Others"))
						{
							ImGui::PushItemWidth(110);
							ImGui::Checkbox(("Damage-Indicator"), &g_Options.Visuals.DamageIndicator);
							ImGui::Checkbox(("AimDirection"), &g_Options.Visuals.barrel);
							ImGui::SameLine();
							ImGui::SliderInt(("Amount##barrel"), &g_Options.Visuals.barrelL, 0, 300);
							ImGui::PopItemWidth();
							ImGui::Checkbox(("Backtrack Hitbox"), &g_Options.Visuals.Hitbox);
							ImGui::SliderFloat(("##duration"), &g_Options.Visuals.HitboxDuration, 0.f, 10.f, "Duration: %.2f");
							ImGui::PushItemWidth(160);
							ImGui::Checkbox(("Bullet Impacts"), &g_Options.Visuals.bulletshow);
							ImGui::SliderFloat("Duration", &g_Options.Visuals.flTracersDuration, 0.f, 10.f, "%.2f");
							ImGui::SliderFloat("Width", &g_Options.Visuals.flTracersWidth, 0.f, 10.f, "%.2f");
							ImGui::PopItemWidth();
						}

					}ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##esppageothers", ImVec2(270, 400), true);
					{

						if (ImGui::CollapsingHeader("Enemy State"))
						{
							ImGui::Checkbox(("Defuser"), &g_Options.Visuals.IsHasDefuser);
							ImGui::Checkbox(("Scoped"), &g_Options.Visuals.Scoped);
							ImGui::Checkbox(("Bomb-Carrier"), &g_Options.Visuals.BombCarrier);
							ImGui::Checkbox(("Flashed"), &g_Options.Visuals.Flashed);
							ImGui::Checkbox(("Distance"), &g_Options.Visuals.Distance);
							ImGui::Checkbox(("Money"), &g_Options.Visuals.Money);
						}

						if (ImGui::CollapsingHeader("World"))
						{

							ImGui::Text("Grenades");
							ImGui::Separator();
							ImGui::Checkbox(("Bomb-ESP"), &g_Options.Visuals.C4World);
							ImGui::PushItemWidth(110);
							ImGui::Combo(("Grenades"), &g_Options.Visuals.Grenades, grenades, ARRAYSIZE(grenades));
							ImGui::SameLine();
							ImGui::Checkbox(("Box"), &g_Options.Visuals.GrenadeBox);
							ImGui::Checkbox(("Grenade-Prediction"), &g_Options.Visuals.GrenadePrediction);
							ImGui::PopItemWidth();

							ImGui::Text("Others");
							ImGui::Separator();

							ImGui::PushItemWidth(110);
							ImGui::Checkbox(("Hostage"), &g_Options.Visuals.Hostage);
							ImGui::SameLine();
							ImGui::Checkbox(("Box##Hostage"), &g_Options.Visuals.HostageBox);
							ImGui::Checkbox(("Chicken"), &g_Options.Visuals.Chicken);
							ImGui::SameLine();
							ImGui::Checkbox(("Box##Chicken"), &g_Options.Visuals.ChickenBox);
							ImGui::Separator();
							ImGui::Checkbox(("Screen Indicator"), &g_Options.Visuals.OffscreenIndicator);
							ImGui::SliderInt(("##size"), &g_Options.Visuals.OffscreenIndicatorSize, 0, 25, "Size: %.2f");
							ImGui::Checkbox(("Dropped Guns"), &g_Options.Visuals.DroppedGuns);
							ImGui::SameLine();
							ImGui::Combo((""), &g_Options.Visuals.DroppedGunsType, droppedWeapons, ARRAYSIZE(droppedWeapons));
							ImGui::Checkbox(("NightMode"), &g_Options.Visuals.nightMode);
							ImGui::Checkbox(("AmbientLight"), &g_Options.Visuals.ambientlight);
							ImGui::Combo(("Skybox Changer"), &g_Options.Visuals.SkyboxChanger, skyboxchanger, ARRAYSIZE(skyboxchanger));
							ImGui::PopItemWidth();
							ImGui::SliderFloat(("##wallalpha"), &g_Options.Visuals.wallalpha, 0.f, 1.f, "Wall Alpha: %.2f");
							ImGui::SliderFloat(("##proppalpha"), &g_Options.Visuals.propalpha, 0.f, 1.f, "Prop Alpha: %.2f");
							ImGui::SliderFloat(("##modelpalpha"), &g_Options.Visuals.modelalpha, 0.f, 1.f, "Model Alpha: %.2f");

							ImGui::Text("Spoof");
							ImGui::Separator();

							ImGui::Checkbox(("mat_drawgray"), &g_Options.Visuals.snowmode);
							ImGui::Checkbox(("mat_showmiplevels"), &g_Options.Visuals.lsdmode);
							ImGui::Checkbox(("r_showenvcubemap"), &g_Options.Visuals.chromemode);
							ImGui::Checkbox(("mat_showlowresimage"), &g_Options.Visuals.minecraftmode);
						}
					}ImGui::EndChild();


					ImGui::SameLine();

					ImGui::BeginChild("##esppage3", ImVec2(270, 400), true);
					{
						btndefault();
						if (ImGui::CollapsingHeader("Chams"))
						{
							ImGui::Checkbox(("Players"), &g_Options.Visuals.Chams);
//							ImGui::Checkbox(("Chams-Local"), &g_Options.Visuals.LocalChams);
							ImGui::Checkbox(("Team"), &g_Options.Visuals.Teamchams);
							ImGui::Checkbox(("HP-Based"), &g_Options.Visuals.chamsHp);
							ImGui::Checkbox(("XQZ"), &g_Options.Visuals.XQZ);
							ImGui::Checkbox(("FakeAngle"), &g_Options.Visuals.FakeAngleChams);
							ImGui::PushItemWidth(160);
							ImGui::Combo("Chams-Style##cmsstyle", &g_Options.Visuals.matierial, "Normal\0\rFlat\0\rWireframe\0\rGlass\0\rGold\0\rPlatinum\0\rPlastic\0\rCrystal\0\0", -1);
							ImGui::SliderInt(("Chams-Alpha##chamsplayeraplha"), &g_Options.Visuals.champlayeralpha, 0, 100);
							ImGui::PopItemWidth();

						}

						if (ImGui::CollapsingHeader("Hands/Weapons"))
						{
							ImGui::PushItemWidth(160);
							ImGui::Combo(("Hands-Style"), &g_Options.Visuals.Hands, HandsMode, ARRAYSIZE(HandsMode));
							ImGui::SliderInt(("Alpha##HandsAlphaa"), &g_Options.Visuals.HandsAlpha, 0, 100);
							ImGui::Separator();
							ImGui::Combo(("Weapon-Style"), &g_Options.Visuals.chamswphands, chamswp, ARRAYSIZE(chamswp));
							ImGui::SliderInt(("Alpha##chamswphands"), &g_Options.Visuals.chamswphandsalpha, 0, 100);
							ImGui::PopItemWidth();
						}
						if (ImGui::CollapsingHeader("Glow-Players"))
						{
							ImGui::PushItemWidth(160);

							ImGui::Checkbox(("Glow Enable"), &g_Options.Visuals.GlowEnable);
							ImGui::Checkbox(("Glow Players"), &g_Options.Visuals.GlowPlayerEnable);
							ImGui::Checkbox(("Glow Enemies"), &g_Options.Visuals.GlowEnemy);
							ImGui::Checkbox(("Glow Team"), &g_Options.Visuals.GlowTeam);
							ImGui::SliderFloat(("Enemy"), &g_Options.Visuals.EnemyAlpha, 0.f, 255.f);
							ImGui::SliderFloat(("Team"), &g_Options.Visuals.TeamAlpha, 0.f, 255.f);

							ImGui::PopItemWidth();
						}

						if (ImGui::CollapsingHeader("Glow-Others"))
						{


							ImGui::PushItemWidth(160);
							ImGui::Checkbox(("Glow-Weapons"), &g_Options.Visuals.GlowWeaponsEnable);
							ImGui::SliderFloat(("Glow-Alpha##glowalpha2"), &g_Options.Visuals.WeaponsGlowAlpha, 0.f, 255.f);

							ImGui::Separator();

							ImGui::Checkbox(("Glow-C4"), &g_Options.Visuals.GlowC4Enable);
							ImGui::SliderFloat(("Glow-Alpha##glowalpha3"), &g_Options.Visuals.C4GlowAlpha, 0.f, 255.f);

							ImGui::PopItemWidth();
						}



					}ImGui::EndChild();


				}


				if (esppages == 1)
				{

					btndefault();


					ImGui::BeginChild("##esppage4", ImVec2(250, 400), true);
					{
						ImGui::Text("Rage");
						ImGui::Separator();
						ImGui::Checkbox(("Angle Lines"), &g_Options.Visuals.angleLines);
						ImGui::SameLine();
						ImGui::Checkbox(("Name"), &g_Options.Visuals.angleLinesName);
						ImGui::Checkbox(("LBY Indicator"), &g_Options.Visuals.LBYIndicator);
						ImGui::Checkbox(("Resolve Mode"), &g_Options.Visuals.resolveMode);
						ImGui::Checkbox(("Rage-Info"), &g_Options.Visuals.RageDraw);
					}ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##esppage5", ImVec2(250, 400), true);
					{
						if (ImGui::CollapsingHeader("Thirdperson"))
						{
							ImGui::PushItemWidth(150);
							ImGui::Checkbox("Enable Thirdperson", &g_Options.Visuals.Enabletp);
							ImGui::Hotkey("##KeyTP", &g_Options.Visuals.TPKey, ImVec2(150, 25));
							ImGui::SameLine();
							ImGui::Text("Key");
							ImGui::Checkbox("Disable On Grenade", &g_Options.Visuals.GrenadeCheck);
							ImGui::Checkbox("Transparency", &g_Options.Visuals.transparency);


							ImGui::PopItemWidth();
						}


						if (ImGui::CollapsingHeader("FOV"))
						{
							ImGui::PushItemWidth(180);
							ImGui::Checkbox(("Enable-FOVInGame"), &g_Options.Visuals.FOVChanger_enabled);
							ImGui::SliderFloat(("FOV"), &g_Options.Visuals.FOVChanger, 0, 120, "%.0f");
							ImGui::Separator();
							ImGui::Checkbox(("Enable-viewmodelFOV"), &g_Options.Visuals.viewmodelChanger_enabled);
							ImGui::SliderFloat(("VFOV"), &g_Options.Visuals.viewmodelChanger, 0, 130, "%.0f");
							ImGui::PopItemWidth();
						}

					}ImGui::EndChild();

					ImGui::SameLine();

					ImGui::BeginChild("##esppage6", ImVec2(250, 400), true);
					{
						if (ImGui::CollapsingHeader("Crosshairs"))
						{
							ImGui::PushItemWidth(110);
							ImGui::Checkbox(("Auto-Wall Crosshair"), &g_Options.Visuals.AWallCrosshair);
							ImGui::Separator();
							ImGui::Checkbox(("Sniper Crosshair"), &g_Options.Visuals.SniperCrosshair);
							ImGui::SameLine();
							ImGui::Combo((""), &g_Options.Visuals.SniperCrosshairType, snipercrosshair, ARRAYSIZE(snipercrosshair));
							ImGui::PopItemWidth();
							ImGui::Separator();
							ImGui::PushItemWidth(110);
							ImGui::Checkbox(("Recoil Crosshair"), &g_Options.Visuals.RecoilCrosshair);
							ImGui::SameLine();
							ImGui::Combo(("##Type"), &g_Options.Visuals.RecoilCrosshair2, rccrosshair, ARRAYSIZE(rccrosshair));
							ImGui::PopItemWidth();
							ImGui::Separator();
							ImGui::PushItemWidth(110);
							ImGui::Checkbox(("Spread Crosshair"), &g_Options.Visuals.SpreadCrosshair);
							ImGui::SliderFloat(("Spread Alpha##alphafill"), &g_Options.Visuals.spread_crosshair_amount, 0.f, 255.f);
							ImGui::PopItemWidth();
						}
						if (ImGui::CollapsingHeader("Removals"))
						{
							ImGui::PushItemWidth(110);
							ImGui::Combo(("Smoke"), &g_Options.Visuals.Smoke, smoke, ARRAYSIZE(smoke));
							ImGui::Checkbox(("No Flash"), &g_Options.Visuals.NoFlash);
							ImGui::Checkbox(("No Scope"), &g_Options.Visuals.noscopeborder);
							ImGui::Checkbox(("No Visual Recoil"), &g_Options.Visuals.NoVisualRecoil);
							ImGui::Checkbox(("No Post Processing"), &g_Options.Visuals.NoPostProcess);
							ImGui::PopItemWidth();
						}

					}ImGui::EndChild();
				}
			}

			if (page == 4)
			{

				style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

				static int selectedItem = 0;
				ImVec2 lastCursor = ImGui::GetCursorPos();

				ImGui::ListBoxHeader("##0", ImVec2(240, 460));
				for (int i = 0; i < Global::ColorsForPicker1.size(); i++)
				{
					bool selected = i == selectedItem;

					if (ImGui::Selectable(Global::ColorsForPicker1[i].Name, selected))
						selectedItem = i;
				}
				ImGui::ListBoxFooter();


				ImGui::SameLine(0.0f, 15.0f);

				ImGui::BeginChild("#generalcolors", ImVec2(450, 460), false, ImGuiWindowFlags_NoScrollbar);
				{
					style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);

					ImGui::BeginChild("#ColorsChild", ImVec2(420, 130), true);
					{
						style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);

						ImGui::Spacing();
						ImGui::Spacing();
						ColorP col = Global::ColorsForPicker1[selectedItem];
						int r = (col.Ccolor[0] * 255.f);
						int g = (col.Ccolor[1] * 255.f);
						int b = (col.Ccolor[2] * 255.f);
						ImGui::PushItemWidth(290);
						ImGui::SliderInt("##red", &r, 0, 255, "%.0f"); ImGui::SameLine(); ImGui::Text("Red Amount");
						ImGui::Spacing();
						ImGui::SliderInt("##green", &g, 0, 255, "%.0f"); ImGui::SameLine(); ImGui::Text("Green Amount");
						ImGui::Spacing();
						ImGui::SliderInt("##blue", &b, 0, 255, "%.0f"); ImGui::SameLine(); ImGui::Text("Blue Amount");
						ImGui::PopItemWidth();
						col.Ccolor[0] = r / 255.0f;
						col.Ccolor[1] = g / 255.0f;
						col.Ccolor[2] = b / 255.0f;

					}ImGui::EndChild();


					ImGui::BeginChild("#colorpreview", ImVec2(420, 320), true);
					{
						style.Colors[ImGuiCol_ChildWindowBg] = ImColor(10, 10, 10, 255);

						ColorP col = Global::ColorsForPicker1[selectedItem];
						ImGui::ColorPicker("##COLOR_PICKER", col.Ccolor);

					}ImGui::EndChild();

				}ImGui::EndChild();


			}

			if (page == 5) // (*g_ClientState)->ForceFullUpdate();
			{
				orginalchild();
				static char filterWeapons[32];
				static char filterSkins[32];

				ImGui::Checkbox(("ENABLE-SKINCHANGER"), &g_Options.Skinchanger.Enabled);

				ImGui::BeginChild("first child", ImVec2(205, 350), true);
				{
					btndefault();

					ImGui::PushItemWidth(-1);
					ImGui::InputText(("##FILTERWEAPONS"), filterWeapons, IM_ARRAYSIZE(filterWeapons));
					ImGui::PopItemWidth();
					ImGui::ListBoxHeader(("##GUNS"), ImVec2(-1, -1));
					for (auto it : ItemDefinitionIndexMap)
					{
						bool isDefault = (int)it.first < 0;
						if (!isDefault && !Contains(ToLower(std::string(filterWeapons)), ToLower(ItemDefinitionIndexMap.at(it.first).entityName)))
							continue;

						if (IsUtility(it.first))
							continue;

						const bool item_selected = ((int)it.first == (int)g_Options.Menu.currentWeapon);

						std::string formattedName;

						formattedName = ItemDefinitionIndexMap.at(it.first).entityName;
						if (ImGui::Selectable(formattedName.c_str(), item_selected))
						{
							g_Options.Menu.currentWeapon = (int)it.first;
						}

					}
					ImGui::ListBoxFooter();
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("second child", ImVec2(205, 350), true);
				{
					btndefault();

					std::string skinName = weaponnames(g_Options.Menu.currentWeapon);
					{
						ImGui::PushItemWidth(-1);
						ImGui::InputText(("##FILTERSKINS"), filterSkins, IM_ARRAYSIZE(filterSkins));
						ImGui::InputInt(("##customID"), &g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin);
						ImGui::PopItemWidth();
						ImGui::ListBoxHeader(("##SKINS"), ImVec2(-1, -1));
						std::string skinStr = "";
						int curItem = -1;
						int s = 0;
						for (auto skin : g_Options.Skinchanger.weaponSkins[skinName])
						{
							int pk = g_Options.Skinchanger.skinMap[skin].paintkit;
							if (pk == g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin)
								curItem = s;
							bool selected = g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin == pk;


							skinStr = g_Options.Skinchanger.skinNames[g_Options.Skinchanger.skinMap[skin].tagName].c_str();
							skinStr += " | ";
							skinStr += std::to_string(g_Options.Skinchanger.skinMap[skin].paintkit);
							if (!Contains(ToLower(std::string(filterSkins)), ToLower(skinStr)))
								continue;
							if (ImGui::Selectable(skinStr.c_str(), selected))
							{
								pk = g_Options.Skinchanger.skinMap[skin].paintkit;
								g_Options.Skinchanger.W[g_Options.Menu.currentWeapon].ChangerSkin = pk;
								FullUpdate();
								break;
							}
							s++;
						}

						ImGui::ListBoxFooter();
					}
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("third child", ImVec2(205, 350), true);
				{
					btndefault();

					ImGui::ListBoxHeader("##KNIVES", ImVec2(-1, -1));
					{


						if (ImGui::RadioButton(("Default"), &g_Options.Skinchanger.knifemodel, 0))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Bayonet"), &g_Options.Skinchanger.knifemodel, 1))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Flip Knife"), &g_Options.Skinchanger.knifemodel, 2))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Gut Knife"), &g_Options.Skinchanger.knifemodel, 3))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Karambit"), &g_Options.Skinchanger.knifemodel, 4))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("M9 Bayonet"), &g_Options.Skinchanger.knifemodel, 5))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Huntsman"), &g_Options.Skinchanger.knifemodel, 6))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Falchion"), &g_Options.Skinchanger.knifemodel, 7))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Bowie"), &g_Options.Skinchanger.knifemodel, 8))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Butterfly Knife"), &g_Options.Skinchanger.knifemodel, 9))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Shadow Daggers"), &g_Options.Skinchanger.knifemodel, 10))
						{
							FullUpdate();
						}

					}
					ImGui::ListBoxFooter();
				}ImGui::EndChild();
				ImGui::SameLine();

				ImGui::BeginChild("fourth child", ImVec2(205, 350), true);
				{
					btndefault();



					ImGui::ListBoxHeader("##Gloves", ImVec2(-1, -1));
					{


						if (ImGui::RadioButton(("Default"), &g_Options.Skinchanger.glove, 0))
						{
							FullUpdate();
						}

						if (ImGui::RadioButton(("Bloodhound"), &g_Options.Skinchanger.glove, 1))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Sport"), &g_Options.Skinchanger.glove, 2))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Driver"), &g_Options.Skinchanger.glove, 3))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Hand Wraps"), &g_Options.Skinchanger.glove, 4))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Motorcycle"), &g_Options.Skinchanger.glove, 5))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Specialst"), &g_Options.Skinchanger.glove, 6))
						{
							FullUpdate();
						}
						if (ImGui::RadioButton(("Hydra"), &g_Options.Skinchanger.glove, 7))
						{
							FullUpdate();
						}

						const char* gstr;
						if (g_Options.Skinchanger.glove == 1)
						{
							gstr = "Charred\0\rSnakebite\0\rBronzed\0\rGuerilla\0\0";
						}
						else if (g_Options.Skinchanger.glove == 2)
						{
							gstr = "Hedge Maze\0\rPandoras Box\0\rSuperconductor\0\rArid\0\Vice\0\Omega\0\Amphibious\0\Bronze Morph\0";
						}
						else if (g_Options.Skinchanger.glove == 3)
						{
							gstr = "Lunar Weave\0\rConvoy\0\rCrimson Weave\0\rDiamondback\0\Overtake\0\Racing Green\0\King Snake\0\Imperial Plaid\0";
						}
						else if (g_Options.Skinchanger.glove == 4)
						{
							gstr = "Leather\0\rSpruce DDPAT\0\rSlaughter\0\rBadlands\0\Cobalt Skulls\0\Overprint\0\Duct Tape\0\Arboreal\0";
						}
						else if (g_Options.Skinchanger.glove == 5)
						{
							gstr = "Eclipse\0\rSpearmint\0\rBoom!\0\rCool Mint\0\Turtle\0\Transport\0\Polygon\0\POW!\0";
						}
						else if (g_Options.Skinchanger.glove == 6)
						{
							gstr = "Forest DDPAT\0\rCrimson Kimono\0\rEmerald Web\0\rFoundation\0\Crimson Web\0\Buckshot\0\Fade\0\Mogul\0";
						}
						else if (g_Options.Skinchanger.glove == 7)
						{
							gstr = "Case Hardened\0\rRattler\0\rMangrove\0\rEmerald\0\0";
						}
						else
						{
							gstr = "";
						}
						ImGui::PushItemWidth(-1);
						if (ImGui::Combo(("##2"), &g_Options.Skinchanger.gloveskin, gstr, -1))
							FullUpdate();

						ImGui::Checkbox(("Skin ID List"), &g_Options.Skinchanger.SkinFilter);

						ImGui::PopItemWidth();

					}ImGui::ListBoxFooter();


				}ImGui::EndChild();

				if (ImGui::Button(("Apply##skinchanger"), ImVec2(845, 30)))
				{
					FullUpdate();
				}


			}

			if (page == 6)
			{

				orginalchild();
				orginalbuttons();

				static int miscpages = 0;

				if (ImGui::Button("Misc I", ImVec2(405.0f, 30.0f)))
				{
					miscpages = 0;
				}

				ImGui::SameLine();

				if (ImGui::Button("Misc II", ImVec2(405.0f, 30.0f)))
				{
					miscpages = 1;
				}

				ImGui::Separator();

				if (miscpages == 0)
				{
					orginalchild();
					btndefault();


					ImGui::BeginChild("#miscchild1", ImVec2(260, 370), true);
					{
						ImGui::Text("Misc1");
						ImGui::Separator();
						ImGui::PushItemWidth(100);
						ImGui::Checkbox(("Rank Revealer"), &g_Options.Misc.ServerRankRevealAll);
						ImGui::Checkbox(("Auto-Accept"), &g_Options.Misc.AutoAccept);
						ImGui::Checkbox(("Bunny Hop"), &g_Options.Misc.Bhop);
						ImGui::Combo(("Auto Strafe"), &g_Options.Misc.AutoStrafe, autostrafe, ARRAYSIZE(autostrafe));
						ImGui::Checkbox(("Watermark"), &g_Options.Misc.Watermark);
						ImGui::Checkbox(("Spectator List"), &g_Options.Misc.SpecList);
						ImGui::Checkbox(("Hitmarker"), &g_Options.Misc.Hitmarker);
						ImGui::SameLine();
						ImGui::Combo(("Sound"), &g_Options.Misc.Hitsound, HitmarkSound, ARRAYSIZE(HitmarkSound));
						ImGui::Checkbox(("Damage Event Logs"), &g_Options.Misc.eventlogs);// - - - - - \
																										 >	 Only have one of these on at a time
						ImGui::Checkbox(("Purchase Event Logs"), &g_Options.Misc.eventlogs2);// - - - /
						if (ImGui::Checkbox(("AfkBot"), &g_Options.Misc.afkbot))
						{
							if (g_Options.Misc.afkbot)
							{

								g_Engine->ClientCmd_Unrestricted("+forward;+moveleft;+left");

							}
							else if (!g_Options.Misc.afkbot)
							{
								g_Engine->ClientCmd_Unrestricted("-forward;-moveleft;-left");
							}
						}

					}ImGui::EndChild();

					ImGui::SameLine(0.0f, 15.0f);

					ImGui::BeginChild("#miscchild2", ImVec2(260, 370), true);
					{


						ImGui::Text("Misc2");
						ImGui::Separator();


						ImGui::Checkbox("Enable Inventory", &g_Options.Misc.inventoryalwayson);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Enables the inventory in-game (competitive games, etc.)");

					}ImGui::EndChild();

					ImGui::SameLine(0.0f, 15.0f);

					ImGui::BeginChild("#miscchild3", ImVec2(260, 370), true);
					{

						orginalbuttons();

						ImGui::Text("Misc3");
						ImGui::Separator();

						if (ImGui::CollapsingHeader("NickName"))
						{
							ImGui::PushItemWidth(230);
							static char nickname[127] = "";
							ImGui::InputText("##NICKNAME", nickname, 127);
							ImGui::PopItemWidth();
							if (ImGui::Button("SetNickname", ImVec2(230, 20)))
							{
								NameChanger::SetName(std::string(nickname).c_str());
							}
							if (ImGui::Button("No Name", ImVec2(230, 20)))
							{
								NameChanger::SetName("\n\xAD\xAD\xAD");
							}
							if (ImGui::Button("Name(Prometheus)", ImVec2(230, 20)))
							{
								static char nicknamePrometheus[11] = "Prometheus";
								NameChanger::SetName(std::string(nicknamePrometheus).c_str());
							}
							if (ImGui::Button("Silent Name", ImVec2(230, 20)))
							{
								misc::silentname(local);
							}

						}


						if (ImGui::CollapsingHeader("ChatSpam"))
						{

							ImGui::PushItemWidth(120);
							ImGui::Checkbox(("ChatSpammer"), &g_Options.Misc.spammeron);
							ImGui::Combo(("SpammerList##chatspam"), &g_Options.Misc.spammer, spammerlist, ARRAYSIZE(spammerlist));
							ImGui::PopItemWidth();
						}


						if (ImGui::CollapsingHeader("ClanTag"))
						{


							ImGui::Checkbox("Promethe.us Clantag", &g_Options.Misc.syncclantag);

							ImGui::Separator();

							ImGui::Text("CustomClantag")
								;
							static char ClanChanger[127] = "";

							ImGui::InputText(("##ClantagINPUT"), ClanChanger, 127, ImGuiInputTextFlags_AllowTabInput);
							ImGui::SameLine();
							if (ImGui::Button(("Change")))
							{
								SetClantag(ClanChanger);
							}

						}


					}ImGui::EndChild();
				}

				if (miscpages == 1)
				{

					ImGui::BeginChild("#RadarChild", ImVec2(260, 370), true);
					{
						ImGui::Text("Radar");

						ImGui::Separator();

						ImGui::Checkbox(("Engine Radar"), &g_Options.Misc.radaringame);

						if (g_Options.Misc.radaringame == true)
						{
							g_Options.Misc.radarwindow = false;
						}
						if (g_Options.Misc.radarwindow == true)
						{
							g_Options.Misc.radaringame = false;
						}

						ImGui::Checkbox("Radar Window", &g_Options.Misc.radarwindow);

						ImGui::SliderFloat("##radrzom", &g_Options.Misc.radrzoom, 0.f, 4.f, "zoom: %.2f");
						ImGui::SliderFloat("##radralpha", &g_Options.Misc.radralpha, 0.f, 1.f, "Alpha: %.2f");
						ImGui::SliderInt(("##Size"), &g_Options.Misc.radrsize, 100, 500, "Size: %.0f");


					}ImGui::EndChild();
					ImGui::SameLine();

					ImGui::BeginChild("Config", ImVec2(370, 120), true);
					{
						ImGui::Text("Config");
						ImGui::Separator();

						static char buff[128];

						ImGui::InputText("##cfgname", buff, 20);

						if (ImGui::Button("Save Config"))
							Config->Save(buff);
						ImGui::SameLine();
						if (ImGui::Button("Load Config"))
							Config->Load(buff);
					}ImGui::EndChild();



				}


			}

			if (g_Options.Skinchanger.SkinFilter)
			{
				SkinFilter();
			}

		}ImGui::End();

	}

}