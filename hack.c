////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// File:     hack.c                                                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Author:   Jorge F.M. Rinaldi                                               //
// Contact:  jorge.madronal.rinaldi@gmail.com                                 //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// Date:     2012/10/23                                                       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ruby.h>

static VALUE rb_mHack;
static VALUE rb_cEmbeddedValue;


VALUE EmbeddedValue_new(VALUE self, VALUE fixnum)
{
	self = Qtrue;
	return self;
}

/* For creating my own VALUES at Ruby level */
VALUE Hack_VALUE(VALUE self, VALUE obj)
{
	VALUE value;

	switch (TYPE(obj)) {
		case T_FIXNUM:
			value = NUM2INT(obj);
			if (!(value % 4)) 
				return Qnil;
			return value;
		default:
			return Qnil;
	}
}

VALUE Hack_IMMEDIATE_P(VALUE self, VALUE obj)
{
	return INT2NUM(IMMEDIATE_P(obj));
}

VALUE Hack_RTEST(VALUE self, VALUE obj)
{
	return RTEST(obj);
}

VALUE Hack_rb_special_const_p(VALUE self, VALUE obj)
{
	return INT2NUM(rb_special_const_p(obj));		
}

VALUE Hack_rb_singleton_class(VALUE self, VALUE obj)
{
	return rb_singleton_class(obj);		
}

void Init_hack(void)
{
	rb_mHack = rb_define_module("Hack");

	rb_cEmbeddedValue = 
		rb_define_class_under(rb_mHack, "EmbeddedValue", rb_cFixnum);
	rb_define_singleton_method(rb_cEmbeddedValue,
		"new", EmbeddedValue_new, 1);

	rb_define_singleton_method(rb_mHack, 
		"IMMEDIATE_P", Hack_IMMEDIATE_P, 1);
	rb_define_singleton_method(rb_mHack,
		"RTEST", Hack_RTEST, 1);
	rb_define_singleton_method(rb_mHack, 
		"rb_special_const_p", Hack_rb_special_const_p, 1);
	rb_define_singleton_method(rb_mHack, 
		"VALUE", Hack_VALUE, 1);
	rb_define_singleton_method(rb_mHack,
		"rb_singleton_class", Hack_rb_singleton_class, 1);

	
}
