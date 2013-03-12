#!/usr/bin/php
<?PHP

include("codebase_parser.inc");

function main($argv) {
$file = $argv[1];
print "File is $file\n";;

$contents =  file_get_contents($file);
$lines = split("\n", $contents);

$descr = _codebase_parse_description($lines);
print "Description = $descr\n";

$keywords = _codebase_parse_keywords($lines);
print ("Keywords = ");
print_r($keywords);
print ("\n");

$subject = _codebase_parse_subject($lines);
print ("subject = ") ;
print_r($subject) ;
print ("\n");

$line = 10;
print "parse_auth\n";
print_r(_codebase_parse_auth($lines, $line));

print "parse_textbook\n";
print_r(_codebase_parse_textbook($lines, $line));


$metadata = _codebase_parse_metadata($lines);

print_r($metadata);

}

main($argv);
