#pragma once

#include "skse64_common/Utilities.h"

namespace RE
{
	// 0C
	struct ObScriptParam
	{
		enum Type
		{
			kType_String = 0,
			kType_Integer = 1,
			kType_Float = 2,
			kType_ObjectReference = 4,
			kType_ActorValue = 5,
			kType_Actor = 6,
			kType_SpellItem = 7,
			kType_Axis = 8,
			kType_Cell = 9,
			kType_AnimationGroup = 0x0A,
			kType_MagicItem = 0x0B,
			kType_Sound = 0x0C,
			kType_Topic = 0x0D,
			kType_Quest = 0x0E,
			kType_Race = 0x0F,
			kType_Class = 0x10,
			kType_Faction = 0x11,
			kType_Sex = 0x12,
			kType_Object = 0x15,
			kType_VariableName = 0x16,
			kType_QuestStage = 0x17,
			kType_MapMarker = 0x18,
			kType_ActorBase = 0x19,
			kType_Coontainer = 0x1A,
			kType_WorldSpace = 0x1B,
			kType_CrimeType = 0x1C,
			kType_Package = 0x1D,
			kType_MagicEffect = 0x1F,
			//kType_Form = 0x20,
			kType_Weather = 0x21,
			kType_Owner = 0x23,
			kType_EffectShader = 0x24,
			kType_FormList = 0x25,
			kType_Perk = 0x27,
			kType_Note = 0x28,
			kType_MiscellaneousStat = 0x29,
			kType_ImagespaceModifier = 0x2A,
			kType_EventFunction = 0x2E,
			kType_EventMember = 0x2F,
			kType_EventData = 0x30,
			kType_Voice = 0x31,
			kType_EncounterZone = 0x32,
			kType_Message = 0x34,
			kType_ObjectID = 0x35,
			kType_Alignment = 0x36,
			kType_EquipType = 0x37,
			kType_Music = 0x39,
			kType_Keyword = 0x3B,
			kType_RefType = 0x3C,
			kType_Location = 0x3D,
			kType_Form = 0x3E,
			kType_QuestAlias = 0x3F,
			kType_Shout = 0x40,
			kType_WordOfPower = 0x41,
			kType_Scene = 0x43,
			kType_Hand = 0x44,		// right hand or left hand
			kType_AssociationType = 0x45,
			kType_WardState = 0x46,
			kType_PackageData_PossiblyNull = 0x47,
			kType_PackageData_Numeric = 0x48,
			kType_FurnitureAnimType = 0x49,
			kType_FurnitureEntryType = 0x4A,
			kType_VMVariableName = 0x4C,
			kType_PackageData = 0x4E,
			kType_KnowableForm = 0x51,
			kType_Region = 0x52
		};
		const char	* typeStr;	// 00
		UInt32		typeID;		// 08
		bool		isOptional;	// 0C
	};
	STATIC_ASSERT(sizeof(ObScriptParam) == 0x10);


	typedef bool(*ObScript_Execute)(void * paramInfo, void * scriptData, TESObjectREFR * thisObj, void * containingObj, void * scriptObj, void * locals, double * result, void * opcodeOffsetPtr);

	// 50
	struct ObScriptCommand
	{
#pragma pack(push, 1)
		struct Chunk
		{};

		struct StringChunk : public Chunk
		{
			UInt16	length;		// 00
			char	str[1];		// 02

			std::string GetString() const
			{
				return std::string(str, length);
			}

			Chunk * GetNext()
			{
				UInt16 len = *(UInt16*)this;
				return (Chunk*)(str + length);
			}
		};

		struct IntegerChunk : public Chunk
		{
			char	unk00;		// 00
			int		value;		// 01

			int GetInteger() const
			{
				return *(int*)((char*)this + 1);
			}

			Chunk * GetNext()
			{
				UInt16 len = *(UInt16*)this;
				return (Chunk*)(this + 1);
			}
		};
#pragma pack(pop)

		struct ScriptData
		{
			UInt16	opcode;			// 00
			UInt16	chunkSize;		// 02
			UInt16	numParams;		// 04

			Chunk * GetChunk()
			{
				return reinterpret_cast<Chunk*>(reinterpret_cast<UInt64>(this) + 6);
			}

			UInt16	strLen;			// 06
			char	str[1];			// 08
		};

		const char			* longName;		// 00
		const char			* shortName;	// 08
		UInt32				opcode;			// 10
		UInt32				pad14;			// 14
		const char			* helpText;		// 18
		UInt8				needsParent;	// 20
		UInt8				pad21;			// 21
		UInt16				numParams;		// 22
		UInt32				pad24;			// 24
		ObScriptParam		* params;		// 28

		ObScript_Execute	execute;		// 30
		void				* parse;		// 38
		void				* eval;			// 40

		UInt32				flags;			// 48
		UInt32				pad4C;			// 4C
	};


	enum
	{
		kObScript_NumObScriptCommands = 0x02E0,
		kObScript_NumConsoleCommands = 0x01B4,

		kObScript_ScriptOpBase = 0x1000,
		kObScript_ConsoleOpBase = 0x0100,
	};

	extern RelocPtr <ObScriptCommand>	g_firstObScriptCommand;
	extern RelocPtr <ObScriptCommand>	g_firstConsoleCommand;
}