#include "sac_class.hpp"

namespace SAC
{
//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------
// Constructor from file
Sac_Class::Sac_Class(const std::string& file_name)
{
  //---------------------------------------------------------------------------
  // Open binary file
  //---------------------------------------------------------------------------
  std::ifstream file(file_name, std::ifstream::binary);
  if (!file)
  {
    std::cerr << "file could not be read...\n";
  }
  // Make sure we're at the start
  file.seekg(0);
  //---------------------------------------------------------------------------
  // End open binary file
  //---------------------------------------------------------------------------
  // Possible words
  std::array<char, 2 * SAC::word_length> two_words;
  std::array<char, 4 * SAC::word_length> four_words;
  //---------------------------------------------------------------------------
  // Header
  //---------------------------------------------------------------------------
  delta  = SAC::read_next_float(&file);
  depmin = SAC::read_next_float(&file);
  depmax = SAC::read_next_float(&file);
  
  // Skip 'unused'
  SAC::skip_word(&file);
  
  odelta = SAC::read_next_float(&file); 
  b = SAC::read_next_float(&file);
  e = SAC::read_next_float(&file);
  o = SAC::read_next_float(&file);
  a = SAC::read_next_float(&file); 

  // Skip 'internal'
  SAC::skip_word(&file);

  // Arrival time picking headers
  // All -12345
  t0 = SAC::read_next_float(&file); 
  t1 = SAC::read_next_float(&file); 
  t2 = SAC::read_next_float(&file); 
  t3 = SAC::read_next_float(&file); 
  t4 = SAC::read_next_float(&file); 
  t5 = SAC::read_next_float(&file); 
  t6 = SAC::read_next_float(&file); 
  t7 = SAC::read_next_float(&file); 
  t8 = SAC::read_next_float(&file); 
  t9 = SAC::read_next_float(&file); 
  f = SAC::read_next_float(&file); 

  // Resp headers
  // All -12345
  resp0 = SAC::read_next_float(&file); 
  resp1 = SAC::read_next_float(&file); 
  resp2 = SAC::read_next_float(&file); 
  resp3 = SAC::read_next_float(&file); 
  resp4 = SAC::read_next_float(&file);
  resp5 = SAC::read_next_float(&file); 
  resp6 = SAC::read_next_float(&file); 
  resp7 = SAC::read_next_float(&file); 
  resp8 = SAC::read_next_float(&file); 
  resp9 = SAC::read_next_float(&file); 

  // Station headers
  stla = SAC::read_next_float(&file);
  stlo = SAC::read_next_float(&file);
  stel = SAC::read_next_float(&file);
  stdp = SAC::read_next_float(&file);

  // Event headers
  evla = SAC::read_next_float(&file);
  evlo = SAC::read_next_float(&file);
  evel = SAC::read_next_float(&file);
  evdp = SAC::read_next_float(&file);
  mag = SAC::read_next_float(&file);
 
  // User headers
  user0 = SAC::read_next_float(&file); 
  user1 = SAC::read_next_float(&file); 
  user2 = SAC::read_next_float(&file); 
  user3 = SAC::read_next_float(&file); 
  user4 = SAC::read_next_float(&file); 
  user5 = SAC::read_next_float(&file); 
  user6 = SAC::read_next_float(&file); 
  user7 = SAC::read_next_float(&file); 
  user8 = SAC::read_next_float(&file); 
  user9 = SAC::read_next_float(&file); 
  dist = SAC::read_next_float(&file);
  az = SAC::read_next_float(&file);
  baz = SAC::read_next_float(&file);
  gcarc = SAC::read_next_float(&file);

  // Skip 'internal' 
  SAC::skip_word(&file);
  // Skip 'internal'
  SAC::skip_word(&file);

  depmen = SAC::read_next_float(&file); 
  cmpaz = SAC::read_next_float(&file);
  cmpinc = SAC::read_next_float(&file);
  xminimum = SAC::read_next_float(&file); 
  xmaximum = SAC::read_next_float(&file); 
  yminimum = SAC::read_next_float(&file); 
  ymaximum = SAC::read_next_float(&file); 

  // Skip 'unused' (x7)
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);

  // Date_time headers
  nzyear = SAC::read_next_int(&file);
  nzjday = SAC::read_next_int(&file);
  nzhour = SAC::read_next_int(&file);
  nzmin = SAC::read_next_int(&file);
  nzsec = SAC::read_next_int(&file);
  nzmsec = SAC::read_next_int(&file);
  nvhdr = SAC::read_next_int(&file);
  norid = SAC::read_next_int(&file); 
  nevid = SAC::read_next_int(&file); 
  npts = SAC::read_next_int(&file);
 
  // Skip 'internal'
  SAC::skip_word(&file);

  nwfid = SAC::read_next_int(&file); 
  nxsize = SAC::read_next_int(&file); 
  nysize = SAC::read_next_int(&file); 
 
  // Skip 'unused'
  SAC::skip_word(&file);

  iftype = SAC::read_next_int(&file);
  idep = SAC::read_next_int(&file); 
  iztype = SAC::read_next_int(&file); 
  
  // Skip 'unused'
  SAC::skip_word(&file);

  iinst = SAC::read_next_int(&file); 
  istreg = SAC::read_next_int(&file); 
  ievreg = SAC::read_next_int(&file);
  ievtyp = SAC::read_next_int(&file);
  iqual = SAC::read_next_int(&file);
  isynth = SAC::read_next_int(&file);
  imagtyp = SAC::read_next_int(&file);
  imagsrc = SAC::read_next_int(&file); 
  ibody = SAC::read_next_int(&file); 

  // Skip 'unused' (x7)
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);
  SAC::skip_word(&file);

  // Logical headers
  leven = SAC::read_next_bool(&file);
  lpspol = SAC::read_next_bool(&file); 
  lovrok = SAC::read_next_bool(&file);
  lcalda = SAC::read_next_bool(&file);

  // Skip 'unused'
  SAC::skip_word(&file);
  
  // KSTNM is 2 words long (like all other 'K' headers)
  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kstnm = std::string(two_words.data(), two_words.size());

  // KEVNM is 4 words long (special rule!)
  four_words = SAC::read_words<sizeof(four_words)>(&file, 4);
  kevnm = std::string(four_words.data(), four_words.size());

  // All other 'K' headers are 2 words long
  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  khole = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2); 
  ko = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  ka = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt0 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt1 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt2 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt3 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt4 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt5 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt6 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt7 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt8 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kt9 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kf = std::string(two_words.data(), two_words.size());
  
  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kuser0 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kuser1 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kuser2 = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kcmpnm = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  knetwk = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kdatrd = std::string(two_words.data(), two_words.size());

  two_words = SAC::read_words<sizeof(two_words)>(&file, 2);
  kinst = std::string(two_words.data(), two_words.size());
  //---------------------------------------------------------------------------
  // End header
  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Data
  //---------------------------------------------------------------------------
  data = SAC::read_data(&file, npts);
  //---------------------------------------------------------------------------
  // End data
  //---------------------------------------------------------------------------
  
  //---------------------------------------------------------------------------
  // Footer (if nvhdr = 7)
  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // End footer 
  //---------------------------------------------------------------------------
  file.close();
}
//-----------------------------------------------------------------------------
// End constructors
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Writing
//-----------------------------------------------------------------------------
void Sac_Class::write(const std::string& file_name)
{
  std::ofstream file(file_name, std::ios::binary | std::ios::out | std::ios::trunc);
  if (!file)
  {
    std::cerr << "Unable to write file...\n";
  }
  //---------------------------------------------------------------------------
  // Header
  //---------------------------------------------------------------------------
  SAC::write_words(&file, convert_to_word(delta));
  SAC::write_words(&file, convert_to_word(depmin));
  SAC::write_words(&file, convert_to_word(depmax));
  // Fill 'unused'
  SAC::write_words(&file, convert_to_word(depmax));

  SAC::write_words(&file, convert_to_word(odelta));
  SAC::write_words(&file, convert_to_word(b));
  SAC::write_words(&file, convert_to_word(e));
  SAC::write_words(&file, convert_to_word(o));
  SAC::write_words(&file, convert_to_word(a));
  // Fill 'internal'
  SAC::write_words(&file, convert_to_word(a));

  SAC::write_words(&file, convert_to_word(t0));
  SAC::write_words(&file, convert_to_word(t1));
  SAC::write_words(&file, convert_to_word(t2));
  SAC::write_words(&file, convert_to_word(t3));
  SAC::write_words(&file, convert_to_word(t4));
  SAC::write_words(&file, convert_to_word(t5));
  SAC::write_words(&file, convert_to_word(t6));
  SAC::write_words(&file, convert_to_word(t7));
  SAC::write_words(&file, convert_to_word(t8));
  SAC::write_words(&file, convert_to_word(t9));
  SAC::write_words(&file, convert_to_word(f));
  SAC::write_words(&file, convert_to_word(resp0));
  SAC::write_words(&file, convert_to_word(resp1));
  SAC::write_words(&file, convert_to_word(resp2));
  SAC::write_words(&file, convert_to_word(resp3));
  SAC::write_words(&file, convert_to_word(resp4));
  SAC::write_words(&file, convert_to_word(resp5));
  SAC::write_words(&file, convert_to_word(resp6));
  SAC::write_words(&file, convert_to_word(resp7));
  SAC::write_words(&file, convert_to_word(resp8));
  SAC::write_words(&file, convert_to_word(resp9));
  SAC::write_words(&file, convert_to_word(stla));
  SAC::write_words(&file, convert_to_word(stlo));
  SAC::write_words(&file, convert_to_word(stel));
  SAC::write_words(&file, convert_to_word(stdp));
  SAC::write_words(&file, convert_to_word(evla));
  SAC::write_words(&file, convert_to_word(evlo));
  SAC::write_words(&file, convert_to_word(evel));
  SAC::write_words(&file, convert_to_word(evdp));
  SAC::write_words(&file, convert_to_word(mag));
  SAC::write_words(&file, convert_to_word(user0));
  SAC::write_words(&file, convert_to_word(user1));
  SAC::write_words(&file, convert_to_word(user2));
  SAC::write_words(&file, convert_to_word(user3));
  SAC::write_words(&file, convert_to_word(user4));
  SAC::write_words(&file, convert_to_word(user5));
  SAC::write_words(&file, convert_to_word(user6));
  SAC::write_words(&file, convert_to_word(user7));
  SAC::write_words(&file, convert_to_word(user8));
  SAC::write_words(&file, convert_to_word(user9));
  SAC::write_words(&file, convert_to_word(dist));
  SAC::write_words(&file, convert_to_word(az));
  SAC::write_words(&file, convert_to_word(baz));
  SAC::write_words(&file, convert_to_word(gcarc));
  // Fill 'internal' (x2)
  SAC::write_words(&file, convert_to_word(gcarc));
  SAC::write_words(&file, convert_to_word(gcarc));

  SAC::write_words(&file, convert_to_word(depmen));
  SAC::write_words(&file, convert_to_word(cmpaz));
  SAC::write_words(&file, convert_to_word(cmpinc));
  SAC::write_words(&file, convert_to_word(xminimum));
  SAC::write_words(&file, convert_to_word(xmaximum));
  SAC::write_words(&file, convert_to_word(yminimum));
  SAC::write_words(&file, convert_to_word(ymaximum));
  // Fill 'unused' (x7)
  SAC::write_words(&file, convert_to_word(ymaximum));
  SAC::write_words(&file, convert_to_word(ymaximum));
  SAC::write_words(&file, convert_to_word(ymaximum));
  SAC::write_words(&file, convert_to_word(ymaximum));
  SAC::write_words(&file, convert_to_word(ymaximum));
  SAC::write_words(&file, convert_to_word(ymaximum));
  SAC::write_words(&file, convert_to_word(ymaximum));

  SAC::write_words(&file, convert_to_word(nzyear));
  SAC::write_words(&file, convert_to_word(nzjday));
  SAC::write_words(&file, convert_to_word(nzhour));
  SAC::write_words(&file, convert_to_word(nzmin));
  SAC::write_words(&file, convert_to_word(nzsec));
  SAC::write_words(&file, convert_to_word(nzmsec));
  SAC::write_words(&file, convert_to_word(nvhdr));
  SAC::write_words(&file, convert_to_word(norid));
  SAC::write_words(&file, convert_to_word(nevid));
  SAC::write_words(&file, convert_to_word(npts));
  // Fill 'internal'
  SAC::write_words(&file, convert_to_word(npts));

  SAC::write_words(&file, convert_to_word(nwfid));
  SAC::write_words(&file, convert_to_word(nxsize));
  SAC::write_words(&file, convert_to_word(nysize));
  // Fill 'unused'
  SAC::write_words(&file, convert_to_word(nysize));

  SAC::write_words(&file, convert_to_word(iftype));
  SAC::write_words(&file, convert_to_word(idep));
  SAC::write_words(&file, convert_to_word(iztype));
  // Fill 'unused'
  SAC::write_words(&file, convert_to_word(iztype));

  SAC::write_words(&file, convert_to_word(iinst));
  SAC::write_words(&file, convert_to_word(istreg));
  SAC::write_words(&file, convert_to_word(ievreg));
  SAC::write_words(&file, convert_to_word(ievtyp));
  SAC::write_words(&file, convert_to_word(iqual));
  SAC::write_words(&file, convert_to_word(isynth));
  SAC::write_words(&file, convert_to_word(imagtyp));
  SAC::write_words(&file, convert_to_word(imagsrc));
  SAC::write_words(&file, convert_to_word(ibody));
  // Fill 'unused' (x7)
  SAC::write_words(&file, convert_to_word(ibody));
  SAC::write_words(&file, convert_to_word(ibody));
  SAC::write_words(&file, convert_to_word(ibody));
  SAC::write_words(&file, convert_to_word(ibody));
  SAC::write_words(&file, convert_to_word(ibody));
  SAC::write_words(&file, convert_to_word(ibody));
  SAC::write_words(&file, convert_to_word(ibody));

  SAC::write_words(&file, bool_to_word(leven));
  SAC::write_words(&file, bool_to_word(lpspol));
  SAC::write_words(&file, bool_to_word(lovrok));
  SAC::write_words(&file, bool_to_word(lcalda));
  // Fill 'unused'
  SAC::write_words(&file, bool_to_word(lcalda));

  std::array<char, 2 * word_length> two_words;
  two_words = convert_to_words<sizeof(two_words)>(kstnm, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  std::array<char, 4 * word_length> four_words;
  four_words = convert_to_words<sizeof(four_words)>(kevnm, 4);
  SAC::write_words(&file, std::vector<char>(four_words.begin(), four_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(khole, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(ko, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(ka, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt0, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt1, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt2, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt3, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt4, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt5, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt6, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt7, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt8, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kt9, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kf, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kuser0, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kuser1, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kuser2, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kcmpnm, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(knetwk, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kdatrd, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));

  two_words = convert_to_words<sizeof(two_words)>(kinst, 2);
  SAC::write_words(&file, std::vector<char>(two_words.begin(), two_words.end()));
  //---------------------------------------------------------------------------
  // End header
  //---------------------------------------------------------------------------

  //---------------------------------------------------------------------------
  // Data
  //---------------------------------------------------------------------------
  for (float x : data)
  {
       SAC::write_words(&file, convert_to_word(x));
  }
  //---------------------------------------------------------------------------
  // End data
  //---------------------------------------------------------------------------
  file.close();
}
//-----------------------------------------------------------------------------
// End writing
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Misc
//-----------------------------------------------------------------------------
float Sac_Class::mean()
{
  float sum{};
  // Foreach loop to try to look cleaner
  for (float x : data)
  {
    sum += x;
  }
  return (sum / data.size());
}
//-----------------------------------------------------------------------------
// End misc
//-----------------------------------------------------------------------------

}