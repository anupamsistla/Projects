
<?php
//print numbers 1 to 100 using for loop
// $names=array("h","a","b","c");
// // echo"$names[0]";
// foreach($names as $val){
// 	echo $val."<br/>";
for($i = 1;$i<=100;$i++)
{
	echo $i;
	echo"<br/>";
}

function abc()
{
	$args=func_get_args();
	foreach ($args as $key => $value) {
		echo "args".(%key +1).":".$value;
	}
}
abc();
abc("a","b");
abc("a","c","v");
?>
