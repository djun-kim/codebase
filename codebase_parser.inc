<?PHP
// Extract description
function  _codebase_parse_description($file_lines) {

  $line = 0;
  // skip until we hit the description section
  while (!preg_match('/##+ *DESCRIPTION/i', $file_lines[$line]) 
	 && $line < count($file_lines)) {
    $line ++;
  }
  $line++;

  $descr = "";
  while  (!preg_match('/##+ *ENDDESCRIPTION/i', $file_lines[$line]) &&
	  $line < count($file_lines)) {
    preg_match('/(##+ *)([^ ].*)/', $file_lines[$line], $matches, PREG_OFFSET_CAPTURE);
    $text = $matches[2][0] . "\n";
    $descr .= $text;
    $line ++;
  }
  return $descr;
};

// Extract array of keywords.
function  _codebase_parse_keywords($file_lines) {
  $line = 0;
  // skip until we hit the description section
  while (!preg_match('/##+ *KEYWORDS/i', $file_lines[$line]) 
	 && $line < count($file_lines)) {
    $line ++;
  }

  preg_match('/(##+ *KEYWORDS\(([^)]*)\))/', $file_lines[$line], $matches, PREG_OFFSET_CAPTURE);

  $keywords = split(",", $matches[2][0]);
  
  return $keywords;
};


function _codebase_parse_func($str) {
  $matchexpr = "^## " . "([^ (].*)" . " *\('(.*)'\)";
  preg_match("/$matchexpr/i",$str, $matches, PREG_OFFSET_CAPTURE);
  print_r($matches);
}

function _codebase_parse_metadata($file_lines) {
  $matchexpr = "^## " . "([^ (].*)" . " *\((.*)\)";

  $metadata = array();
  $line = 0;

  while ($line < count($file_lines)-1) {
    $str = $file_lines[$line];
    if (preg_match("/$matchexpr/i",$str, $matches, PREG_OFFSET_CAPTURE)) {
      $label = $matches[1][0];
      $value = $matches[2][0];
      $metadata[$label] = $value;
    }
    $line++;
  }
  return $metadata;
}

function _codebase_parse_args($label, $file_lines, &$line=0) {

  $matchexpr = "^## " . $label . "\('(.*)'\)";
  while (!preg_match(
		     "/$matchexpr/i",
		     $file_lines[$line],
		     $matches, PREG_OFFSET_CAPTURE)
	 && $line < count($file_lines)-1) {
    $line ++;
  }

  print_r($matches);

  return($matches[1][0]);
}

// Extract subject, chapter, section, 
function _codebase_parse_subject($file_lines, &$line = 0) {
  $subject = _codebase_parse_args("DBSUBJECT", $file_lines, $line);
  $chapter = _codebase_parse_args("DBCHAPTER", $file_lines, $line);
  $section = _codebase_parse_args("DBSECTION", $file_lines, $line);

  return array($subject, $chapter, $section);
};

// Extract auth info: author, institution, date
function _codebase_parse_auth($file_lines, &$line = 0) {
  $date = _codebase_parse_args("Date", $file_lines, $line);
  $author = _codebase_parse_args("Author", $file_lines, $line);
  $institution = _codebase_parse_args("Institution", $file_lines, $line);

  return array($date, $author, $institution);
};

// Extract textbook info: titletext1, edition, authortext1, section1, problem1
function _codebase_parse_textbook($file_lines, &$line = 0) {

  print "line = $line\n";;
  $title1 = _codebase_parse_args("TitleText1", $file_lines, $line);
  $edition1 = _codebase_parse_args("EditionText1", $file_lines, $line);
  $author1 = _codebase_parse_args("AuthorText1", $file_lines, $line);
  $section1 = _codebase_parse_args("Section1", $file_lines, $line);
  $problem1 = _codebase_parse_args("Problem1", $file_lines, $line);

  print "line = $line\n";;

  $title2 = _codebase_parse_args("TitleText2", $file_lines, $line);
  $edition2 = _codebase_parse_args("EditionText2", $file_lines, $line);
  $author2 = _codebase_parse_args("AuthorText2", $file_lines, $line);
  $section2 = _codebase_parse_args("Section2", $file_lines, $line);
  $problem2 = _codebase_parse_args("Problem2", $file_lines, $line);

  print "line = $line\n";;

  return array($title1, $author1, $edition1, $section1, $problem1,
	       $title2, $author2, $edition2, $section2, $problem2);

};

?>