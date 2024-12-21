using System;  
using System.Collections.Generic;  
using System.IO;  
using System.Linq;  
using System.Text.RegularExpressions;  
  
class MiniDictionary  
{  
    private Dictionary<string, string> dictionary = new Dictionary<string, string>();  
  
    public MiniDictionary(string filePath)  
    {  
        // 读取词典文件并加载到字典中  
        LoadDictionary(filePath);  
    }  
  
    private void LoadDictionary(string filePath)  
    {  
        try  
        {  
            foreach (var line in File.ReadLines(filePath))  
            {  
                var parts = line.Split(',');  
                if (parts.Length == 2)  
                {  
                    dictionary[parts[0].Trim()] = parts[1].Trim();  
                }  
            }  
        }  
        catch (Exception ex)  
        {  
            Console.WriteLine($"Error loading dictionary: {ex.Message}");  
        }  
    }  
  
    public string Search(string query)  
    {  
        // 精确匹配  
        if (dictionary.TryGetValue(query, out string definition))  
        {  
            return definition;  
        }  
        else  
        {  
            // 模糊匹配，使用正则表达式来匹配包含查询字符串的单词  
            var regex = new Regex(Regex.Escape(query), RegexOptions.IgnoreCase);  
            foreach (var entry in dictionary)  
            {  
                if (regex.IsMatch(entry.Key))  
                {  
                    return entry.Value; // 返回找到的第一个模糊匹配的定义  
                }  
            }  
        }  
        return null; // 如果没有找到匹配项，则返回null  
    }  
}  
  
class Program  
{  
    static void Main(string[] args)  
    {  
        var miniDict = new MiniDictionary("dictionary.txt"); // 替换为你的词典文件路径  
        Console.WriteLine("Enter a word to search for its definition:");  
        string searchTerm = Console.ReadLine();  
        string definition = miniDict.Search(searchTerm);  
        if (definition != null)  
        {  
            Console.WriteLine($"Definition of '{searchTerm}': {definition}");  
        }  
        else  
        {  
            Console.WriteLine($"No definition found for '{searchTerm}'.");  
        }  
    }  
}