<?php
include_once('config.php');
?>

<!DOCTYPE html>
<html lang="en" >
<head>
  <meta charset="UTF-8">
			    <title>Remember Medicines</title>
                <link href="https://fonts.googleapis.com/css?family=Rubik:400,700|Crimson+Text:400,400i" rel="stylesheet">
                 <meta name="description" content="Try and test HTML code online in a simple and easy way using our free HTML editor and see the results in real-time." />
                  <meta charset="UTF-8" />
                  <meta property="og:title" content="Bootstrap 4 Responsive Layout Example" />
                  <meta property="og:description" content="View the live example as well as try and test it using the online HTML editor." />
                  <meta name="robots" content="noindex, nofollow">
                 <link rel="icon" href="<?php echo $base_url;?>assets/images/remember_medicines.png" type="image/x-icon">
                  <link rel="stylesheet" href="<?php echo $base_url;?>assets/css/loginstyle.css">
                  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
                  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
                  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>

</head>
<body>
   <div class="login-container" style="left:35%;top:20%;width: 500px;height:auto;" >
       <form name="loginform" action="<?php echo $base_url;?>actionLogin.php" method="post">
         <a href="<?php echo $base_url;?>" style="text-align: center;">
             <img alt="image" src="<?php echo $base_url; ?>assets/images/remember_medicines.png" class="header-logo" /> </a>
           <div class="form-group">
               <label>Email</label>
               <input class="form-control" type="text" name="email" placeholder="Enter your email here" id="email">
           </div>
           <div class="form-group">
               <label>Password</label>
               <input class="form-control" type="password" name="password" placeholder="Enter your password here" id="password">
           </div>
           <input type="submit" name="login" value="LOGIN">           
       </form>
            <p style="text-align: center;">If you haven't registered, <a style="font-size: 14px;display: inline-block;" href="<?php echo $base_url;?>signup.php">Sign Up</a></p>
            <p style="text-align: center;"> <a style="font-size: 14px;display: inline-block;" href="<?php echo $base_url;?>forgotPassword.php">Forgot Password</a></p>
           
            <div class="social-icons" style="background-color: #d5d4d9;">
               <a class="btn btn-outline-dark" href="<?php echo $login_url;?>" role="button" style="text-transform:none;margin-bottom: 8px;">
                  <img width="20px" style="width:8%;" alt="Google sign-in" src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/53/Google_%22G%22_Logo.svg/512px-Google_%22G%22_Logo.svg.png" />
                  Login with Google
                </a>
            </div>
   </div>

</body>
</html>
