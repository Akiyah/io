#Regex

JID := Object clone do(
//metadoc JID category networking
//metadoc JID description Object for representing JIDs.
  #_jidRegex = "(.+)@([^/]+)/?(.*)?" asRegex

  //doc JID username Extracts username from JID.
  username  ::= nil
  //doc JID host Extracts host's address from JID.
  host      ::= nil
  //doc JID resource Returns defined resource.
  resource  ::= nil
  //doc JID asString Converts JID to string with all available parts included.
  asString  ::= nil

  /*doc JID with(jid) Extracts all parts of a provided <code>Sequence</code> and returns new <code>JID</code> clone.
  <pre><code>
  j := JID with("cow@moo.com/Alpes")
  j username == "cow"
  j host == "moo.com"
  j resource == "Alpes"
  j asString == "cow@moo.com/Alpes"</code></pre>*/
  with := method(jid,
    fpart := jid split("@")
    spart := fpart at(1) split("/")
    #matches := jid allMatchesOfRegex(_jidRegex) ?first ?captures
    #matches at(3) isEmpty ifTrue(matches atPut(3, nil))

    self clone\
      setAsString(jid)\
      setUsername(fpart at(0))\
      setHost(spart at(0))\
      setResource(spart at(1)))
)

//doc Sequence asJid Converts Sequence to JID object. <pre><code>"cow@moo.com/Scandinavia" asJid</code></pre>
Sequence asJid := method(
  JID with(self))
