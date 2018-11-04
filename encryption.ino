#include <xxtea-lib.h>

void encryption_setup(String key) {
  xxtea.setKey(key);
}

String loRa_encrypt(String message) {
  message = xxtea.encrypt(message);

  const String randomToken = (String)random(9999);
  message += randomToken;
  message += randomToken.length();

  return xxtea.encrypt(message);
}

String loRa_decrypt(String message) {
  message = (String)xxtea.decrypt(message);

  const int tokenLength = message.substring(message.length() - 1).toInt();
  message = (String)message.substring(0, message.length() - tokenLength - 1);

  return xxtea.decrypt(message);
}

