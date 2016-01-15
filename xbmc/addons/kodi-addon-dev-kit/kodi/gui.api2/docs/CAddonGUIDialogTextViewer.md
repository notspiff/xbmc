# *<p align="center">Kodi development</p>*
-------------
*<p align="center">
  [<img src="http://kodi.wiki/images/c/c9/Logo.png" alt="Home">](http://kodi.tv/)
  [<img src="http://kodi.wiki/images/5/52/Zappy.png" alt="Home" width="100" height="100">](http://kodi.tv/)
</p>*
*<p align="center">
  [<img src="help.BackButton.png" alt="Back" width="100" height="40">](../Readme.md#CAddonGUIDialogTextViewer)
</p>*
#### *<p align="center">Binary add-on GUI library, Version Level: 2</p>*
## *<p align="center">Text viewer dialog</p>*
-------------

General
-------------

The text viewer dialog can be used to display descriptions, help texts or other larger texts.

In order to achieve a line break is a `\n` directly in the text or in the **"./resources/language/resource.language.??_??/strings.po"** to call with
[`std::string CAddOnLib_General::GetLocalizedString(...);`](../../addon.api2/docs/General.md#CAddOnLib_General_GetLocalizedString).

It has the header [`#include <kodi/gui.api2/GUIDialogTextViewer.h>`](../GUIDialogTextViewer.h) be included to enjoy it.

Functions
-------------

1. [void Show(const std::string& heading, const std::string& text);](#CAddonGUIDialogTextViewer_Show)

-------------

*<p align="center">![SUID](help.GUIDialogTextViewer.png)</p>*

-------------

*  <a id="CAddonGUIDialogTextViewer_Show"></a>
   **`void CAddonGUIDialogTextViewer::Show(const std::string& heading, const std::string& text);`**
    * Show info text dialog
      * **`heading`:** Small heading text
      * **`text`:** Showed text on dialog

    Code example:
    ```cpp
      #include <kodi/gui.api2/GUIDialogTextViewer.h>

      CAddonGUIDialogTextViewer::Show("The Wizard of Oz (1939 film)",
        "The Wizard of Oz is a 1939 American musical comedy-drama fantasy film "
        "produced by Metro-Goldwyn-Mayer, and the most well-known and commercially "
        "successful adaptation based on the 1900 novel The Wonderful Wizard of Oz "
        "by L. Frank Baum. The film stars Judy Garland as Dorothy Gale. The film"
        "co-stars Terry the dog, billed as Toto; Ray Bolger, Jack Haley, Bert Lahr, "
        "Frank Morgan, Billie Burke, Margaret Hamilton, with Charley Grapewin and "
        "Clara Blandick, and the Singer Midgets as the Munchkins.\n"
        "\n"
        "Notable for its use of Technicolor, fantasy storytelling, musical score and "
        "unusual characters, over the years it has become an icon of American popular "
        "culture. It was nominated for six Academy Awards, including Best Picture but "
        "lost to Gone with the Wind. It did win in two other categories including Best "
        "Original Song for \"Over the Rainbow\". However, the film was a box office "
        "disappointment on its initial release, earning only $3,017,000 on a $2,777,000 "
        "budget, despite receiving largely positive reviews. It was MGM's most "
        "expensive production at that time, and did not completely recoup the studio's "
        "investment and turn a profit until theatrical re-releases starting in 1949.\n"
        "\n"
        "The 1956 broadcast television premiere of the film on CBS re-introduced the "
        "film to the wider public and eventually made the presentation an annual "
        "tradition, making it one of the most known films in cinema history. The "
        "film was named the most-viewed motion picture on television syndication by "
        "the Library of Congress who also included the film in its National Film "
        "Registry in its inaugural year in 1989. Designation on the registry calls "
        "for efforts to preserve it for being \"culturally, historically, and "
        "aesthetically significant\". It is also one of the few films on UNESCO's "
        "Memory of the World Register.\n"
        "\n"
        "The Wizard of Oz is often ranked on best-movie lists in critics' and public "
        "polls. It is the source of many quotes referenced in modern popular culture. "
        "It was directed primarily by Victor Fleming (who left production to take "
        "over direction on the troubled Gone with the Wind production). Noel Langley, "
        "Florence Ryerson and Edgar Allan Woolf received credit for the screenplay, "
        "but there were uncredited contributions by others. The songs were written "
        "by Edgar \"Yip\" Harburg (lyrics) and Harold Arlen (music). The incidental "
        "music, based largely on the songs, was composed by Herbert Stothart, with "
        "interspersed renderings from classical composers.\n");
      ```