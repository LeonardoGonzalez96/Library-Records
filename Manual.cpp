
#include "Manual.hpp"


/**
  Default constructor.
  Default-initializes all private members. 
  Booleans are default-initialized to False
*/
Manual::Manual(): has_website_{false}, has_visual_aid_{false}, website_{""}, device_{""}
{	
}

/**
  Parameterized constructor.
  @param     : The title of the book (a string)
  @param     : The author of the book (a string)
  @param     : The number of pages in the book (a positive integer)
  @param     : A flag indicating whether the book is in digital form 
                with DEFAULT VALUE False (a Boolean)
  @param     : The name of the device (a string)
  @param     : The URL that is in the format 
                'https://www.something.something' 
                or 'http://www.something.something' 
                with the last 'something' being at least 2 characters 
                with DEFAULT VALUE empty string (a string)
  @param     : A Boolean indicating the presence of a visual aid 
                with DEFAULT VALUE False
  @post      : The private members are set to the values of the 
                corresponding parameters. 
                If a URL is provided, the website flag is set to True.
                If the URL is ill-formatted, the website is set to 
                empty string and the website flag is set to False.
*/
Manual::Manual(std::string name, std::string author, int page_count, std::string model, bool is_digital, std::string url, bool aid) : Book(name, author, page_count, is_digital), has_visual_aid_{aid}, device_{model}
{
  const std::regex pattern("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
  
  // If website in invalid, set website_ to empty string and set has_website_ to false
  // ** Differs from setWebsite instructions
  if (regex_match(url,pattern)) {
    website_ = url;
    has_website_ = true;
  }
  else {
    website_ = "";
    has_website_ = false;
  }
}

/**
  @return  : the variable indicating the device the manual is for
**/
std::string Manual::getDevice() const
{
  return device_;
}

/**
  @return  : the url for the website
**/
std::string Manual::getWebsite() const
{
  return website_;
}

/**
  @return  : the visual aid flag
**/
bool Manual::hasVisualAid() const
{
  return has_visual_aid_;
}

/**
  @return  : the has website flag
**/
bool Manual::hasWebsite() const
{
  return has_website_;
}

/**
  @param   : a reference to a website link (string) that is in the format 
             'https://www.something.something' 
             or 'http://www.something.something' 
             with the last 'something' being at least 2 characters
  @return  : has_website_ flag (a boolean)
  @post    : If the link is not correctly formatted, 
             store "Broken Link" in the link member variable (see <regex>) 
             and either way set the has website flag to True
**/
// (** Differs from parameterized constructor)
bool Manual::setWebsite(const std::string& site)
{
  const std::regex pattern("((http|https)://)(www.)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
  
  if (regex_match(site,pattern)) {
    website_ = site;
  }
  else {
    website_ = "Broken Link";
  }

  has_website_ = true;

  return has_website_;
} 

/**
  @param  : a reference to a string representing the device
  @post   : sets the private member variable to the value of the parameter
**/
void Manual::setDevice(const std::string& model)
{
  device_ = model;
}

/**
  @param  : a boolean
  @post   : sets the private member variable indicating the presence 
            of a visual aid to the value of the parameter
**/
void Manual::setVisualAid(const bool& aid)
{
  has_visual_aid_ = aid;
}

/**
  @post     : displays Manual data in the form:
  "[title_] is written by [author_] company for device: [device_]. Website: [website_ / Broken Link / NONE]. Page Count: [page_count_]. [It is / It is not] available digitally.\n" 
*/
void Manual::display(){
  std::string web = getWebsite();
  std::string digital = "It is";
  if(getWebsite() == ""){
    web = "NONE";
  }
  if (!(isDigital()))
  {
    digital = "It is not";
  }
  
  std::cout << getTitle() << " is written by " << getAuthor() << " company for device: " << device_ << ". Website: " << web << ". Page Count: " << getPageCount() << ". " << digital << " available digitally.\n";
}

/**
  @param    : a reference to a string key to match the device of the Manual
  @post     : calls display() if the key argument is equal to device_ (e.g. "Oven")   
*/
void Manual::displayFilter(const std::string& key){
  std::string str;
  for(int i = 0; i < device_.length(); i++){
    if(device_[i] != '-'){
      str += device_[i];
    }
    else{
      break;
    }
  }
  if(str == key){
    display();
  }
}

