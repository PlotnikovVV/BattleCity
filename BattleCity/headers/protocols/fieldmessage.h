#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <optional>
#include <variant>
#include <vector>

namespace pv {

	#define GET_ENUMERATOR_VALUE(ENUMERATOR_IDX) (static_cast<uint64_t>(1) << (ENUMERATOR_IDX))

	class FieldMessage {
	public:

		FieldMessage();

		static constexpr size_t MAX_FIELDS_SUPPORTED_COUNT{ 64 };
		enum class Fields : uint64_t {
			MESSAGE_SIZE = GET_ENUMERATOR_VALUE(0),
			CORR_ID = GET_ENUMERATOR_VALUE(1),
			LIGHT_TANK_HEALTH = GET_ENUMERATOR_VALUE(2),
			CURRENT_PLAYER_NAME = GET_ENUMERATOR_VALUE(3),
			GAME_OVER_STR_RESOURCE = GET_ENUMERATOR_VALUE(4),
			HIGHEST_SCORE = GET_ENUMERATOR_VALUE(5),

			//====================================================================
			__LIMIT_FIELD__ = GET_ENUMERATOR_VALUE(MAX_FIELDS_SUPPORTED_COUNT - 1)
		};

		using FieldsUnderlyingType = std::underlying_type_t<FieldMessage::Fields>;

		void SetStringField(Fields, std::string);
		void SetIntField(Fields, int);

		void DeleteField(Fields);

		std::string to_string() const;
		void from_string(const std::string&);

		bool Has(Fields) const;

		int GetInt(Fields) const;
		std::string GetString(Fields) const;

	private:
		
		bool FieldHasType(Fields, const std::string*) const;
		bool FieldIsSet(Fields) const;
		bool FieldIsPresentInEnum(Fields) const;

		//supported field types
		static inline const std::string string_type_name_{ "string" };
		static inline const std::string int_type_name_{ "int" };

		//message field -> corresponding type
		std::unordered_map<Fields, const std::string*> field_to_type_p_;

		using SupportedVariant = std::variant<std::string, int>;
		std::unordered_map<Fields, SupportedVariant> fields_;

		std::vector<FieldsUnderlyingType> enums_masks_;

		static inline size_t message_id_{ 0 };
	};

	inline FieldMessage::Fields operator|(FieldMessage::Fields a, FieldMessage::Fields b)
	{
		return static_cast<FieldMessage::Fields>(
				static_cast< FieldMessage::FieldsUnderlyingType >(a) | 
				static_cast< FieldMessage::FieldsUnderlyingType >(b)
			);
	}

}
