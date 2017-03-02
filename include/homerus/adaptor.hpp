#pragma once
#include <type_traits>
namespace folklore{ namespace homerus
{
	namespace adaptor_category
	{
		struct adaptor_category_tag{};
		struct non_adaptor_category_tag{};
		struct index_adaptor_tag{};
		struct gate1d_adaptor_tag{};
		struct gate2d_adaptor_tag{};
		struct transform_adaptor_tag{};
		struct transform_by_adaptor_tag{};
		struct index_adaptor_category
		{
			typedef index_adaptor_tag        adaptor_tag;
			typedef adaptor_category_tag            type;
		};
		struct gate1d_adaptor_category
		{
			typedef gate1d_adaptor_tag       adaptor_tag;
			typedef adaptor_category_tag            type;
		};
		struct gate2d_adaptor_category
		{
			typedef gate1d_adaptor_tag       adaptor_tag;
			typedef adaptor_category_tag            type;
		};
		struct transform_adaptor_category
		{
			typedef transform_adaptor_tag    adaptor_tag;
			typedef adaptor_category_tag            type;
		};
		struct transform_by_adaptor_category
		{
			typedef transform_by_adaptor_tag adaptor_tag;
			typedef adaptor_category_tag            type;
		};
	}
	namespace impl_
	{
		template <typename T>
		struct indexed_by_t:adaptor_category::index_adaptor_category
		{
		};
		template <typename T>
		struct gate1d_by_t:adaptor_category::gate1d_adaptor_category
		{
		};
		template <typename T>
		struct gate2d_by_t:adaptor_category::gate2d_adaptor_category
		{
		};
		template <typename T>
		struct transform_t:adaptor_category::transform_adaptor_category
		{
			template <typename... Args>
			struct by:adaptor_category::transform_by_adaptor_category
			{
			};
		};
		struct nop
		{
		};
	}
	template <typename Ad_>
	struct adaptor
	{
		typedef typename Ad_::type type;
	};
	template <typename Ind>
	adaptor<impl_::indexed_by_t<Ind>> indexed_by(const uint32_t index)
	{
		return adaptor<impl_::indexed_by_t<Ind>>();
	}
}}
