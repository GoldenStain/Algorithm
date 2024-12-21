using System;
using System.Security.Cryptography;

public class BaiduTranslateSignatureGenerator
{
    private readonly string appid;
    private readonly string secretKey;

    public BaiduTranslateSignatureGenerator(string appid, string secretKey)
    {
        this.appid = appid;
        this.secretKey = secretKey;
    }

    public string GenerateSignature(string query, string salt)
    {
        // Concatenate the request parameters
        string concatenatedString = appid + query + salt + secretKey;

        // Generate the MD5 hash
        using (var md5 = MD5.Create())
        {
            byte[] hashBytes = md5.ComputeHash(Encoding.UTF8.GetBytes(concatenatedString));
            return Convert.ToHexString(hashBytes).ToLower();
        }
    }
}
