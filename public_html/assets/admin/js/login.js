$( document ).ready(function() {
  jQuery("#LoginFrm").validate({
                ignore: [],
                errorClass: "invalid-feedback animated fadeInDown",
                errorElement: "div",
                errorPlacement: function(e, a) {
                    jQuery(a).parents(".form-group > div").append(e)
                },
                highlight: function(e) {
                    jQuery(e).closest(".form-group").removeClass("is-invalid").addClass("is-invalid")
                },
                success: function(e) {
                    jQuery(e).closest(".form-group").removeClass("is-invalid"), jQuery(e).remove()
                },
                rules: {
                    "username": {
                        required: !0,
                        email: !0
                    },
				 "password": {
					 required: !0
				 }
                },
                errorPlacement: function(){
                     return false;
                  },submitHandler: function(form) {
					  
					  $("#imageloder").css("display","block");
						form.submit();
				  },
            });
});