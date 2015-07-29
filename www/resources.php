<?php
set_include_path('include');
require_once("config.inc");
require_once("toolkit/useful.inc");
require_once("toolkit/siteLayout.inc");
require_once('report/listingMessages.inc');
startHead("Aerobatic Flight Schools");
startContent();
?>
<p><a href="index.php">Return to schools listing</a></p>

<div class="title">Resources for Aerobatic Instructors and Students</div>

<div class="section">
<div class="subtitle">Aerobatic School/Instructor Listing Request</div>
<?php
listingInstructions();
?>
<p>Your IAC schools liaison is <?php 
echo "<a href='mailto:".$schools_email."?subject=Flight Schools'>".$schools_name."</a>.\n";
?></p>
</div>

<div class="section">
<div class="subtitle">Feature Articles</div>

<div class="subsection"><img class="headshot"
	src="images/250/Stowell_headshot1.jpg" />
<div class="articleListHeading">Rich Stowell</div>
<ul class="reprints">
	<li><a href="reprints/07april_stowell2.pdf">Normal Upright Spins</a></li>
	<li><a href="reprints/07aug_stowell.pdf">Recreational Aerobatics:
	Flying the Loop</a></li>
	<li><a href="reprints/07jan_stowell.pdf">Recreational Aerobatics:
	Uncoordinated Flight</a></li>
	<li><a href="reprints/07june_stowell.pdf">Recreational Aerobatics:
	Mastering the Aileron Roll</a></li>
	<li><a href="reprints/08april_stowell.pdf">Recreational Aerobatics #10:
	Primary Smooth Award: Turn and Spin</a></li>
	<li><a href="reprints/08june_stowell.pdf">Recreational Aerobatics #11:
	Primary Smooth Award: Loop and Slow Roll</a></li>
	<li><a href="reprints/08aug_stowell.pdf">Recreational Aerobatics #12:
	Primary Smooth Award: Judgement Day</a></li>
	<li><a href="reprints/08feb_smooth.pdf">Measuring Progress with the
	Primary Smooth Award</a></li>
</ul>
<div class="bio">Rich Stowell was the country's first Master Instructor
of Aerobatics. He is the author of the book <span class="title">The
Light Airplane Pilot’s Guide to Stall/Spin Awareness</span>, has been
teaching spins, emergency maneuvers, and aerobatics since 1987, and is
the author of numerous articles on how to fly aerobatics for recreation
and competition. He is based in Santa Paula, California and McCall,
Idaho. For more information visit: <a href="http://www.richstowell.com">www.richstowell.com</a>
</div>
</div>

<div class="subsection"><img class="headshot"
	src="images/250/BuddinPitts.jpg" style="float: left" />
<div class="articleListHeading">Budd Davisson</div>
<ul class="reprints">
    <li><a href="reprints/rvsnyou.pdf">RV's, Aerobatics and You</a></li>
	<li><a href="reprints/07jan_newbs.pdf">Bring on the Newbies</a></li>
	<li><a href="reprints/07sept_traffic.pdf">Taming Traffic Patterns:
	Special Airplanes have Special Needs</a></li>
</ul>
<div class="bio">Besides being incredibly good looking (considering the
miles and lack of maintenance) and humble, Budd has been instructing
aerobatics for 41 years, 37 years of it in a Pitts and has carved out a
niche teaching low-time pilots (high-time ones too), how to land a Pitts
and other high-performance taildraggers in all situations, on all
runways. He's based in Phoenix and runs a Bed &amp; Breakfast in
conjunction with the school. For more information visit: <a
	href="http://www.airbum.com">www.airbum.com</a></div>
</div>

<div class="subsection"><img class="headshot"
	src="images/250/Koontz_small_crop.jpg" style="float: left" />
<div class="articleListHeading">Greg Koontz</div>
<ul class="reprints">
	<li><a href="reprints/07oct_noninverted.pdf">Very Basic Flipping:
	Aerobatics in airplanes without inverted systems</a></li>
	<li><a href="reprints/08may_emerg.pdf">Emergency Thinking: Have a Plan
	Before You Need It</a></li>
	<li><a href="reprints/08july_teach.pdf">Teaching the Basic Aerobatics
	Course: Part One: Laying a Good Foundation</a></li>
	<li><a href="reprints/08sept_teach.pdf">Teaching the Basic Aerobatics
	Course: Part Two: The First Lesson</a></li>
	<li><a href="reprints/08nov_koontz.pdf">Teaching the Basic Aerobatics
	Course: Part Three: The Second Lesson Plan</a></li>
	<li><a href="reprints/09jan_koontz.pdf">Teaching the Basic Aerobatics
	Course: Part Four: The Third Lesson Plan</a></li>
	<li><a href="reprints/09march_koontz.pdf">Teaching the Basic Aerobatics
	Course: Part Five The Final Lesson Plan</a></li>
</ul>
<div class="bio">Greg Koontz is a NAFI Master Certificated Flight
Instructor-Aerobatic and has been teaching basic aerobatic courses since
1974. He is a full-time aerobatic professional sponsored by American
Champion Aircraft flying shows in his Super Decathlon, is an aerobatic
competency evaluator (ACE), and is a member of the International Council
of Air Shows’ ACE Committee. He is based in Ashville, Alabama. For more
information visit: <a href="http://www.gkairshows.com">www.gkairshows.com</a>
</div>
</div>

<div class="subsection"><img class="headshot"
	src="images/250/DSC_3522.JPG" style="float: left" />
<div class="articleListHeading">Additional Articles</div>
<ul class="reprints">
	<li><a href="reprints/IAC-Finding Quality Aerobatic Instructionx.pdf">Finding
  Quality Aerobatic Instruction</a><span class="author">by Miriam
  Levin</span></li>
    <li><a href="reprints/rvcomp.pdf">Can RVs Contend in the IAC?</a><span
        class="author">by Jeff Stoltenberg</span></li>
	<li><a href="reprints/07july_achvmnt.pdf">IAC Achievement Awards
	Program Enters the 21st Century</a><span class="author">by Vicki Cruse</span></li>
	<li><a href="reprints/07july_landings.pdf">Smooth Takeoffs and Landings</a><span
		class="author">by Bill Finagin</span></li>
	<li><a href="reprints/07may_hasenberg.pdf">Why Do I need Training?</a><span
		class="author">by Oliver Hasenberg</span></li>
	<li><a href="reprints/08aug_rollisa.pdf">A Roll is a Roll or Is It?</a><span
		class="author">by Gordon Penner</span></li>
	<li><a href="reprints/08march_sick.pdf">Aerobatics and Airsickness:
	Tips for a Smooth Flight</a> <span class="author">by Jim Zazas</span></li>
	<li><a href="reprints/09apr_whitson.pdf">Aerobatics: Why You Should!</a><span 
	    class="author">by Randy Whitson</span></li>
</ul>
</div>
</div>

<div class="section">
<div class="subtitle">IAC Chapters</div>
<p>If you are interested in getting involved with an IAC Chapter in your
area, you can search for IAC Chapters using this link <a
	href="http://www.eaa.org/chapters/locator/">Chapter Search</a>. If
there is no Chapter in your immediate area and you wish to start an IAC
Chapter, please visit <a
	href="http://www.eaa.org/chapters/activities/startachapter.asp">How to
Start an IAC Chapter</a>.</p>
</div>

<p><a href="index.php">Return to schools listing</a></p>
<?php
endContent();
?>
