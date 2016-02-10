# Discord-Twitch-Teambot

This project was developed for "The Anime Club" Twitch team: http://www.twitch.tv/team/TheAnimeClub

The purpose of this project was to keep the members of The Anime Club informed about the status of other streamers in The Anime Club. When a streamer starts livestreaming, the bot updates a Discord channel that the stream just started. It updates the channel every 5 minutes.

It accesses the internet to gather information about the streamers' statuses by crawling http://www.twitch.tv/team/TheAnimeClub/live_member_list to find members who are live. This is because Twitch has NO TEAMS API, so all access to Twitch teams have to be through the data they put on the website, and parsed to gather relevant data.
