#pragma once

#include "tes_binding.h"
#include "collections.h"
#include "tes_context.h"

namespace reflection { namespace binding {

    using namespace collections;

    struct ObjectConverter {

        typedef HandleT tes_type;

        static HandleT convert2Tes(object_base* obj) {
            return obj ? obj->tes_uid() : 0;
        }

        static object_stack_ref convert2J(HandleT hdl) {
            return tes_context::instance().getObjectRef((Handle)hdl);
        }

    };

    template<class T, class P> struct GetConv < boost::intrusive_ptr_jc<T, P>& > : ObjectConverter{
        static boost::intrusive_ptr_jc<T, P> convert2J(HandleT hdl) {
            return tes_context::instance().getObjectRefOfType<T>((Handle)hdl);
        }
    };

    template<> struct GetConv < object_stack_ref& > : ObjectConverter{};
    //template<> struct GetConv < object_stack_ref > : ObjectConverter{};

    template<> struct GetConv < object_base* > : ObjectConverter{};
    template<> struct GetConv < array* > : ObjectConverter{};
    template<> struct GetConv < map* > : ObjectConverter{};
    template<> struct GetConv < form_map* > : ObjectConverter{};

    //////////////////////////////////////////////////////////////////////////

    template<class T, class P> struct j2Str < boost::intrusive_ptr_jc<T, P> > {
        static function_parameter typeInfo() { return j2Str<T*>::typeInfo(); }
    };

    template<class T, class P> struct j2Str < boost::intrusive_ptr_jc<T, P>& > {
        static function_parameter typeInfo() { return j2Str<T*>::typeInfo(); }
    };

    struct jc_object_type_info {
        static function_parameter typeInfo() { return function_parameter_make("int", "object"); }
    };

    template<> struct j2Str < object_base * > : jc_object_type_info{};
    template<> struct j2Str < map * > : jc_object_type_info{};
    template<> struct j2Str < array * > : jc_object_type_info{};
    template<> struct j2Str < form_map * > : jc_object_type_info{};
}
}
