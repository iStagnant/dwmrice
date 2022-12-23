----------------------------------
-- @name    FlameScans
-- @url     https://flamescans.org
-- @author  elias
-- @license MIT
----------------------------------


---@alias manga { name: string, url: string, author: string|nil, genres: string|nil, summary: string|nil }
---@alias chapter { name: string, url: string, volume: string|nil, manga_summary: string|nil, manga_author: string|nil, manga_genres: string|nil }
---@alias page { url: string, index: number }


----- IMPORTS -----
Html = require("html")
Headless = require("headless")
Time = require("time")
--- END IMPORTS ---




----- VARIABLES -----
Browser = Headless.browser()
Page = Browser:page()
Base = "https://flamescans.org"
Delay = 1 -- seconds
--- END VARIABLES ---



----- MAIN -----

--- Searches for manga with given query.
-- @param query string Query to search for
-- @return manga[] Table of mangas
function SearchManga(query)
    local url = Base .. "/ygd/?s=" .. query:gsub(" ", "+")
    Page:navigate(url)
    Time.sleep(Delay)

    local mangas = {}

    for i, v in ipairs(Page:elements(".bsx > a")) do
        local manga = { url = v:attribute("href"), name = v:attribute("title") }
        mangas[i + 1] = manga
    end

    return mangas

end


--- Gets the list of all manga chapters.
-- @param mangaURL string URL of the manga
-- @return chapter[] Table of chapters
function MangaChapters(mangaURL)
    Page:navigate(mangaURL)
    Time.sleep(Delay)

    local chapters = {}

    for i, v in ipairs(Page:elements("#chapterlist > ul li")) do
        local n = tonumber(v:attribute("data-num"))
        local base = Html.parse(v:html()):find("a"):first()

        local chapter = { url = base:attr("href"), name = base:find("span"):first():text():gsub("\n", " ") }

        if n ~= nil then
            chapters[n] = chapter
        end
    end

	return chapters
end


--- Gets the list of all pages of a chapter.
-- @param chapterURL string URL of the chapter
-- @return page[]
function ChapterPages(chapterURL)
    Page:navigate(chapterURL)
    Time.sleep(Delay)

    local pages = {}

    for i, v in ipairs(Page:elements("#readerarea p img")) do
        local page = { index = i, url = v:attribute("src") }
        pages[i + 1] = page
    end

	return pages
end

--- END MAIN ---




----- HELPERS -----
--- END HELPERS ---

-- ex: ts=4 sw=4 et filetype=lua
