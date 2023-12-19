<?php 
include_once('config.php');
?>
<!DOCTYPE html>
	<html>
			<head>
			    <title>remembermedicines</title>
                <meta name="viewport" content="width=device-width, maximum-scale=1, minimum-scale=1">
                <link href="https://fonts.googleapis.com/css?family=Rubik:400,700|Crimson+Text:400,400i" rel="stylesheet">
                 <meta name="description" content="Try and test HTML code online in a simple and easy way using our free HTML editor and see the results in real-time." />
                  <meta charset="UTF-8" />
                  <meta property="og:title" content="Bootstrap 4 Responsive Layout Example" />
                  <meta property="og:description" content="View the live example as well as try and test it using the online HTML editor." />
                  <meta name="robots" content="noindex, nofollow">
                  
                  <link rel="icon" href="<?php echo $base_url;?>assets/images/remember_medicines.png" type="image/x-icon">
				  <link rel="stylesheet" href="<?php echo $base_url; ?>assets/fonts/icomoon/style.css">
				  <link rel="stylesheet" href="<?php echo $base_url; ?>assets/css/bootstrap.min.css">
				  <link rel="stylesheet" href="<?php echo $base_url; ?>assets/css/magnific-popup.css">
				  <link rel="stylesheet" href="<?php echo $base_url; ?>assets/css/jquery-ui.css">

				  <link rel="stylesheet" href="<?php echo $base_url; ?>assets/css/aos.css">	
			      <link rel="stylesheet" href="<?php echo $base_url; ?>assets/css/style.css">
			      <link rel="stylesheet" href="<?php echo $base_url; ?>assets/css/custom.css">

			    </head>
			<body>     

                <div class=" container-fluid site-wrap">
					   <!-- header start -->             	
					    <div class="site-navbar py-2">

					      <div class="search-wrap">
					          <a href="#" class="search-close js-search-close"><span class="icon-close2"></span></a>
					          <form action="#" method="post">
					            <input type="text" class="form-control" placeholder="Search keyword and hit enter...">
					          </form>
					      </div>  

					      <div class="container">
					    <div class="row">
					          <div class="col-lg-4 col-md-4 col-sm-12 col-xs-12 logo">
					             <!--  <a href="<?php echo $base_url;?>index.php" class="js-logo-clone">MediCare</a>
 -->
                                     <div class="site-logo">
                                    <a href="index.php" class="js-logo-clone">  
        					              <img src="<?php echo $base_url;?>assets/images/remember_medicines.png" alt="logo" class="logo">
        					              </a>
                                    </div>
					             
					          </div>
					          <div class="col-lg-8 col-md-8 col-sm-12 col-xs-12  main-nav">
					            <nav class="site-navigation text-right text-md-center" role="navigation">
					              <ul class="site-menu js-clone-nav">
					                <li><a href="#aboutme">About Us</a></li>
					                <li><a href="#contact">Contact</a></li>
					                <li><a href="<?php echo $base_url;?>login.php">Login</a></li>
					              </ul>
					            </nav>
					          </div>					         
					        </div>
					      </div>
					    </div>
                        <!-- header end -->
 
					    <!-- banner start-->
					     <div class="site-blocks-cover" style="background-image: url('assets/images/hero_1.jpg');">
						      <div class="container">
						        <div class="row">
						          <div class="col-lg-7 mx-auto order-lg-2 align-self-center">
						            <div class="site-block-cover-content text-center">
						              <h2 class="sub-title">Never forget to take your medicines with remembermedicines!</h2>
						              <h1>Welcome To remembermedicines</h1>
						              <p>
						                <a href="<?php echo $base_url;?>signup.php" class="btn btn-primary px-5 py-3">Sign Up</a>
						              </p>
						            </div>
						          </div>						          
						        </div>
						      </div>
						    </div>

                            <!--banner end -->
                             <!-- tabs start -->

							<div class="site-section" id="medicines">
							<div class="container">
							<div class="row align-items-stretch section-overlap">
							  <div class="col-md-6 col-lg-4 mb-4 mb-lg-0">
							    <div class="banner-wrap bg-primary h-100">
							      <a href="#" class="h-100">
							        <h5>Never forget<br>Your Medicines</h5>
							        <p>
							          Register your account on remembermedicines for free!
							         
							        </p>
							      </a>
							    </div>
							  </div>
							  <div class="col-md-6 col-lg-4 mb-4 mb-lg-0">
							    <div class="banner-wrap h-100">
							      <a href="#" class="h-100">
							        <h5>Forget<br>Then Regret!</h5>
							        <p>
							          Never forget to take your Medicines with remembermedicines
							          
							        </p>
							      </a>
							    </div>
							  </div>
							  <div class="col-md-6 col-lg-4 mb-4 mb-lg-0">
							    <div class="banner-wrap bg-warning h-100">
							      <a href="#" class="h-100">
							        <h5>Register<br>Now!</h5>
							        <p>
							          Join the remembermedicines family!
							          
							        </p>
							      </a>
							    </div>
							  </div>

							</div>
							</div>
							</div>


                              <!-- tabs end -->

				<!-- About us start-->
				<div class="container" id="aboutme">
					<h1>About Us</h1>
					<p class="dumpkey">remembermedicines is app created to help those, taking numerous amount of medications to remember to take their medications without fail. Once the user enters the Medicines page, the user will be redirected to a page where login using various social accounts or create a new account and  enter the time in a search bar of the medicines option in the navigation bar and retrieve the medicines they need to in that specific time frame of 1 hour, its picture, expiry and means for taking it.</p>	
				</div>

				<!-- About us end-->	


                           <!--footer start -->

							   <footer class="site-footer" id="contact">
							      <div class="container">
							        <div class="row">
							          <div class="col-lg-6 col-md-6 col-sm-12  col-xs-12 class="dumpkey"">

							              <h2 class="footer-heading">REMEMBERMEDICINES</h2>
							              <p>remembermedicines is a web application created by Anupam, a 12th grader studying the International Baccaluarette. remembermedicines is an application created to remind the user to take their medications which are meant to be taken at specific time periods and display the medication's expiry date, photo and means for taking it.
							              </p>

							          </div>
							          <div class="col-lg-2 col-md-2 col-sm-12  col-xs-12">
							            <h3 class="footer-heading mb-4">Quick Links</h3>
							            <ul class="list-unstyled">
								                <li><a href="#aboutme">About Us</a></li>
								                <li><a href="#contact">Contact</a></li>
								                <li><a href="<?php echo $base_url; ?>login.php">Register/Login</a></li>
							            </ul>
							          </div>

							          <div class="col-lg-3 col-md-3 col-sm-12  col-xs-12">
							            <div class="block-5 mb-5">
							              <h3 class="footer-heading mb-4">Contact Info</h3>
							              <ul class="list-unstyled">
							                <li class="address">Singapore, Singapore</li>
							                <li class="phone"><a href="tel://23923929210">+65 6673 0557</a></li>
							                <li class="email">help@remembermedicines.com</li>
							              </ul>
							            </div>


							          </div>
							        </div>
							      </div>
							    </footer>
                           <!-- footer end -->
			        <div class="row text-center" id="footerCP">
			          <div class="col-md-12">
			            <p>
			              
			              Copyright &copy;
			             All rights reserved | <a href="index.php" target="_blank"
			                class="text-primary">remembermedicines</a>
			              
			            </p>
			          </div>

			        </div>

                </div>
                <script src='https://www.google.com/recaptcha/api.js' async defer ></script>
			</body>
   </html>

