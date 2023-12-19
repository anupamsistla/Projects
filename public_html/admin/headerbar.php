 <div class="navbar-bg"></div>
      <nav class="navbar navbar-expand-lg main-navbar sticky">
        <div class="form-inline mr-auto">
          <ul class="navbar-nav mr-3">
            <li><a href="#" data-toggle="sidebar" class="nav-link nav-link-lg
									collapse-btn"> <i data-feather="align-justify"></i></a></li>
            <li><a href="#" class="nav-link nav-link-lg fullscreen-btn">
                <i data-feather="maximize"></i>
              </a></li>
            <!-- <li>
              <form class="form-inline mr-auto">
                <div class="search-element">
                  <input class="form-control" type="search" placeholder="Search" aria-label="Search" data-width="200">
                  <button class="btn" type="submit">
                    <i class="fas fa-search"></i>
                  </button>
                </div>
              </form>
            </li> -->
          </ul>
        </div>
<?php 
// $requestdata='';
// $CI =& get_instance();
// $CI->load->model('UserModel');
// $CI->load->model('CustomerModel');
// $CI->load->model('ComplainModel');
// $CI->load->library('session');
// $userid=$CI->session->userdata("userId");
// $useraccount=$CI->UserModel->getUseraccount($userid); 

// if(!$useraccount==''){
//       $adminid= get_object_vars($useraccount);
//       $uid= $adminid["uacc_group_fk"];
//       $customerid= $adminid["customer_id"];
//     }

// $requestdata= $varAdvertdata["ComplainList"] = $CI->ComplainModel->requestComplainListtotal($uid,$customerid);
?>        
        <ul class="navbar-nav navbar-right">
         
          <li class="dropdown">
            <a href="#" data-toggle="dropdown" class="nav-link dropdown-toggle nav-link-lg nav-link-user"> 
              <img alt="image" src="<?php echo $base_url;?>assets/admin/img/user-img.png" 
                 class="user-img-radious-style"> 
                 <span class="d-sm-none d-lg-inline-block"></span>
              </a>
           
            <div class="dropdown-menu dropdown-menu-right pullDown">
              <a href="#" class="dropdown-item has-icon"> 
                 <i class="fas fa-user"></i><?php echo $_SESSION['user']['name'];?>
                <?php 
                //   $custaccount=$CI->CustomerModel->getCustomer(md5($customerid)); 
                //   if(!empty($custaccount)){
                //     $customerUserid=$custaccount->cust_userid;
                //      if($uid=='1')
                //       { 
                //           echo "<b>Administrator</b>:<br>".$this->session->userdata("user_id");
                //           } 
                //       else {
                //         if($uid=='13'){
                //              echo"<b>Admin:</b><br>".$this->session->userdata("user_id");
                //              echo"<b>Referral Code:</b><br>".$customerUserid;
                //           }else{
                //               echo"<b>Admin:</b><br>".$this->session->userdata("user_id");
                //           }
                //       }
                // }?>
              </a>
           
              <div class="dropdown-divider"></div>
                <a href="<?php echo $base_url;?>admin/updateUser.php?id=<?php echo $_SESSION['user']['userId'];?>" class="dropdown-item has-icon text-danger"> 
                   <i class="fas fa-user-circle"></i>Profile
                </a>
                <a href="<?php echo $base_url;?>admin/logout.php/" class="dropdown-item has-icon text-danger"> 
                  <i class="fas fa-sign-out-alt"></i>Logout
                </a>
            </div>
          </li>
        </ul>
      </nav>