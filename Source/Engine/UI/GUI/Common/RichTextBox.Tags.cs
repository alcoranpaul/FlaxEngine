// Copyright (c) 2012-2022 Wojciech Figat. All rights reserved.

using FlaxEngine.Utilities;

namespace FlaxEngine.GUI
{
    partial class RichTextBox
    {
        private static void ProcessBr(ref ParsingContext context, ref HtmlTag tag)
        {
            context.Caret.X = 0;
            var style = context.StyleStack.Peek();
            var font = style.Font.GetFont();
            if (font)
                context.Caret.Y += font.Height;
        }
        
        private static void ProcessColor(ref ParsingContext context, ref HtmlTag tag)
        {
            if (tag.IsSlash)
            {
                context.StyleStack.Pop();
            }
            else
            {
                var style = context.StyleStack.Peek();
                if (tag.Attributes.TryGetValue(string.Empty, out var colorText))
                {
                    if (Color.TryParse(colorText, out var color))
                    {
                        style.Color = color;
                    }
                }
                context.StyleStack.Push(style);
            }
        }

        private static void ProcessAlpha(ref ParsingContext context, ref HtmlTag tag)
        {
            if (tag.IsSlash)
            {
                context.StyleStack.Pop();
            }
            else
            {
                var style = context.StyleStack.Peek();
                if (tag.Attributes.TryGetValue(string.Empty, out var alphaText))
                {
                    if (alphaText.Length == 3 && alphaText[0] == '#')
                    {
                        style.Color.A = ((StringUtils.HexDigit(alphaText[1]) << 4) + StringUtils.HexDigit(alphaText[2])) / 255.0f;
                    }
                    else if (alphaText.Length > 1 && alphaText[alphaText.Length - 1] == '%')
                    {
                        style.Color.A = float.Parse(alphaText.Substring(0, alphaText.Length - 1)) / 100.0f;
                    }
                }
                context.StyleStack.Push(style);
            }
        }

        private static void ProcessStyle(ref ParsingContext context, ref HtmlTag tag)
        {
            if (tag.IsSlash)
            {
                context.StyleStack.Pop();
            }
            else
            {
                var style = context.StyleStack.Peek();
                if (tag.Attributes.TryGetValue(string.Empty, out var styleName))
                {
                    if (context.Control.Styles.TryGetValue(styleName, out var customStyle))
                    {
                        if (customStyle.Font == null)
                            customStyle.Font = style.Font;
                        style = customStyle;
                    }
                }
                context.StyleStack.Push(style);
            }
        }

        private static void ProcessBold(ref ParsingContext context, ref HtmlTag tag)
        {
            if (tag.IsSlash)
            {
                context.StyleStack.Pop();
            }
            else
            {
                var style = context.StyleStack.Peek();
                style.Font = style.Font.GetBold();
                context.StyleStack.Push(style);
            }
        }

        private static void ProcessItalic(ref ParsingContext context, ref HtmlTag tag)
        {
            if (tag.IsSlash)
            {
                context.StyleStack.Pop();
            }
            else
            {
                var style = context.StyleStack.Peek();
                style.Font = style.Font.GetItalic();
                context.StyleStack.Push(style);
            }
        }
    }
}