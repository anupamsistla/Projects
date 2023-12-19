$(document).ready(function()
{

    // my method for validate username
    
    $.validator.addMethod("username_regex", function(value, element) 
    {
         return this.optional(element) || /^[a-z0-9\.\-_]{3,30}$/i.test(value);
    },   "Please enter a username with only a-z 0-9.");
 
var form=$("#loginform").val();
    form.validate(

    {

        rules:
        {

            

            'username':{

                required: true,

                minlength: 3,

                username_regex: true,

                remote:{

                    url: "validatorAJAX.php/username",

                    type: "post"

                }
             },

            

            },

           
            'password':{

                required: true,

                minlength: 8

            },



        },

        messages:{

            

            'username':{

                required: "The username field is mandatory!",

                minlength: "Choose a username of at least 4 letters!",

                username_regex: "You have used invalid characters. Are permitted only letters numbers!",

                remote: "The username is already in use by another user!"

            },

            
            'password':{

                required: "The password field is mandatory!",

                minlength: "Please enter a password at least 8 characters!"

            },

          

        },submitHandler:
        function(form)
        {
            form.submit();
        }

    });


