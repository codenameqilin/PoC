#pragma once

template<typename obj_t>
struct CObjDisposer
{
	void
	operator()(
		__inX obj_t* obj
		)
	{
		delete obj;
	}
};

template<typename type_t>
struct CRefObjDisposer
{
	static
	void
	ReleaseRef(
		__in_opt type_t* obj
		)
	{
		if (!obj->DecreaseReferenceHolders())
			CObjDisposer<type_t>()(obj);
	}
	void
	operator()(
		__inX type_t* obj
		)
	{
		ReleaseRef(obj);
	}
};
