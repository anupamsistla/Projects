<div class="main-sidebar sidebar-style-2">
        <aside id="sidebar-wrapper">
          <div class="sidebar-brand">
            <a href="<?php echo $base_url; ?>">
             <img alt="image" src="<?php echo $base_url; ?>assets/images/remember_medicines.png" class="header-logo" /> 
              <!-- <span class="logo-name">MediCare</span> -->
            </a>
          </div>
          <ul class="sidebar-menu">
               <li class="menu-header">User Interface</li> 

          <?php   if($_SESSION['user_permission'][0]['moduleId']=='1' && $_SESSION['user_permission'][0]['permissionView']=='Y') {?>
                <li class="dropdown">
                  <a href="<?php echo $base_url;?>admin/Dashboardlist.php" class="nav-link">
                    <i class="fa fa-desktop"></i><span>Dashboard</span>
                  </a>
                </li>
                <?php } ?>
                 <?php   if($_SESSION['user_permission'][1]['moduleId']=='2' && $_SESSION['user_permission'][1]['permissionView']=='Y') {?>
          
                <li class="dropdown">
                  <a href="<?php echo $base_url;?>admin/Rolelist.php" class="nav-link">
                    <i class="fa fa-book"></i><span>Role List</span>
                  </a>
                </li>
                <?php } ?>
               <?php   if($_SESSION['user_permission'][2]['moduleId']=='3' && $_SESSION['user_permission'][2]['permissionView']=='Y') {?>
             
                <li class="dropdown">
                  <a href="<?php echo $base_url;?>admin/Permissionlist.php" class="nav-link">
                    <i class="fa fa-check"></i><span>Permission List</span>
                  </a>
                </li>
            <?php }?>
               <?php   if($_SESSION['user_permission'][3]['moduleId']=='4' && $_SESSION['user_permission'][3]['permissionView']=='Y') {?>
          
                <li class="dropdown">
                  <a href="<?php echo $base_url;?>admin/Userlist.php" class="nav-link">
                    <i class="fa fa-user"></i><span>User List</span>
                  </a>
                </li>
                <?php } ?>
     <?php   if($_SESSION['user_permission'][4]['moduleId']=='5' && $_SESSION['user_permission'][4]['permissionView']=='Y') {?>
             
                <li class="dropdown">
                  <a href="<?php echo $base_url;?>admin/Medicinelist.php" class="nav-link">
                    <i class="fa fa-medkit"></i><span>Medicine List</span>
                  </a>
                </li>
            <?php }?>
            
            
          </ul>
  </aside>
</div>