$(document).ready(function()
{

    //my method for validate username
    
    $.validator.addMethod("username_regex", function(value, element) 
    {
         return this.optional(element) || /^[a-z0-9\.\-_]{3,30}$/i.test(value);
    },   "Please enter a username with only a-z 0-9.");
    $.validator.addMethod("lettersonly", function(value, element) 
    {
         return this.optional(element) || /^[a-zA-Z]*$/i.test(value);
    },   "Please enter data in letters only.");
  
    $.validator.addMethod("letterswithspace", function(value, element) 
    {
         return this.optional(element) || /^[a-zA-Z ]*$/i.test(value);
    },  "Please enter data in letters only.");

    $.validator.addMethod("digitonly", function(value, element) 
    {
         return this.optional(element) || /^[0-9]/.test(value);
    },  "Please enter data in digits only.");

//var form=$("#signupform").val();
    $("#signupform").validate(

    {

        rules:
        {

            'name':{

                required: true,
                letterswithspace:true,
                minlength: 1
                },

            'username':{

                required: true,

               minlength: 3,

                username_regex: true,

                // remote:{

                //     url: "validatorAJAX.php/usernamecheck",

                //     type: "post"

                // }
             },

            'email':{

                required: true,

                 email: true,

                // remote:{

                // url: "validatorAJAX.php/emailcheck",

                // type: "post"

                // }

            },

           
            'password':{

                required: true,

                 minlength: 8

            },

            'confirmpassword':{

                equalTo: '#password'

                },

            'gender':{
                required:true,
              
            },

            'age':{
                required:true,
                digitonly:true
            },
            'medicalcondition':{
                required:true,
                letterswithspace:true,
                minlength:300

            },
            'doctorcontact':{
                minlength:14,
                digitonly:true
            },

        },

        messages:{

            'name':{

                required: "The name field is mandatory!",

                minlength: "Choose a name of at least 1 letters!",

            },

            'username':{

                required: "The username field is mandatory!",

                 minlength: "Choose a username of at least 4 letters!",

                 username_regex: "You have used invalid characters. Are permitted only letters numbers!",

                // remote: "The username is already in use by another user!"

            },

            'email':{

                required: "The Email is required!",

                 email: "Please enter a valid email address!",

                // remote: "The email is already in use by another user!"

            },
            'password':{

                required: "The password field is mandatory!",

                 minlength: "Please enter a password at least 8 characters!"

            },

            'confirmpassword':{

               equalTo: "The two passwords do not match!"
            },

            'age':{
                required:"Your age is required!",
            },
            'medicalcondition':{
                required:"This field is mandatory",
                minlength:"Exceded the minimun length of characters!"
            },
            'doctorcontact':{
                minlength:"Exceded length of 14 digits!"
            },

        },
        submitHandler:function(form)
        {
            form.submit();
        }

    });


    $("#loginform").validate(

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

    $("#updateUser").validate(

    {

        rules:
        {

            'name':{

                required: true,
                letterswithspace:true,
                  minlength: 1
                },

            'username':{

                required: true,

               minlength: 3,

                username_regex: true,

                // remote:{

                //     url: "validatorAJAX.php/usernamecheck",

                //     type: "post"

                // }
             },

            'email':{

                required: true,

                 email: true,

                // remote:{

                // url: "validatorAJAX.php/emailcheck",

                // type: "post"

                // }

            },

           
            'password':{

                required: true,

                 minlength: 8

            },

            'gender':{
                required:true,
              
            },

            'age':{
                required:true,
                digitonly:true,
            },
            'medicalcondition':{
                required:true,
                letterswithspace:true,
                minlength:300

            },
            'doctorcontact':{
                minlength:14,
                digitonly:true
            },
        },

        messages:{

            'name':{

                required: "The name field is mandatory!",

                minlength: "Choose a name of at least 1 letters!",

            },

            'username':{

                required: "The username field is mandatory!",

                 minlength: "Choose a username of at least 4 letters!",

                 username_regex: "You have used invalid characters. Are permitted only letters and numbers!",

                // remote: "The username is already in use by another user!"

            },

            'email':{

                required: "The Email is required!",

                 email: "Please enter a valid email address!",

                // remote: "The email is already in use by another user!"

            },
            'password':{

                required: "The password field is mandatory!",
                 minlength: "Please enter a password at least 8 characters!"

            },
            'age':{
                required:"Your age is required!",
            },
            'medicalcondition':{
                required:"This field is mandatory",
                minlength:"Exceded the minimun length of characters!"
            },
            'doctorcontact':{
                minlength:"Exceded length of 14 digits!"
            }
        },
        submitHandler:function(form)
        {
            form.submit();
        }

    });

    $("#addMedicine").validate(
    {
        rules:
        {
            'name':{

                required: true,
                },

            'type':{

                required: true,
             },

            'medicalCondition':{
                required:true,
                letterswithspace:true
            },           
            'day':{
                required: true
            },

            'medTime':{
                required:true,              
            },

            'expiryDate':{
                required:true,
            },
            'meansTotake':{
                required:true,
                maxlength:300,
               letteronly:true
            },
             'image':{
                required:true,
            },
            'importance':{
                maxlength:300,
                requird: true,
              letteronly:true
            },
        },

        messages:{

            'expiryDate':{
                required:"this field is required",
            },
            'meansTotake':{
                 maxlength: "Exceded the maximum length of characters 300",
            },
            'importance':{
                requird: "this field is required",
            },
        },
        submitHandler:function(form)
        {
            form.submit();
        }

    });


   $("#updatemedicine").validate(
    {
        rules:
        {
            'name':{

                required: true
                },

            'type':{

                required: true,
             },

            'medicalCondition':{
                required:true,
                letterswithspace:true
            },           
            'day':{
                required: true,
            },

            'medTime':{
                required:true,              
            },

            'expiryDate':{
                required:true,
            },
            'meansTotake':{
                required:true,
                maxlength:300,
               letteronly:true
            },
             'image':{
                required:true,
            },
            'importance':{
                maxlength:300,
                requird: true,
              letteronly:true
            },
        },

        messages:{
            'meansTotake':{
                 maxlength: "Exceded the maximum length of characters 300",
            },
            'importance':{
                 maxlength: "Exceded the maximum length of characters 300",
            },
        },
        submitHandler:function(form)
        {
            form.submit();
        }

    });
});
