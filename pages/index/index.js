// index.js
// 获取应用实例
const app = getApp()
var interval;
Page({
    data: {
        isHiddenMsg: false,
        announcementText: "补习班刷榜活动火爆开始啦，朋友圈集赞拿好礼，还有免费课程赠送哦！",
        //滚动速度
        step: 1,
        //初始滚动距离
        distance: 0, 
        space: 30,
        // 时间间隔
        interval: 20, 
        swiperList:[{
            "imageUrl":"http://101.42.35.137:8080/sliderWidget1.jpg"
        },
        {
            "imageUrl":"http://101.42.35.137:8080/sliderWidget2.jpg"
        },
        {
            "imageUrl":"http://101.42.35.137:8080/sliderWidget3.jpg"
        }],
        visitCount:20,
        indexImageMax:10,
        //活动结束时间
        overTime:1682870400,
        overDay:0,
        overHour:0,
        overMinute:0,
        overSecond:0,
    },
    onLoad(){
        this.topScroll();
        this.getVisit((result)=>{
            this.setData({"visitCount":result})
        });

        // this.formatTime((day,hour,minute,second)=>{
        //     this.setData({
        //         "overDay":day,
        //         "overHour":hour,
        //         "overMinute":minute,
        //         "overSecond":second,
        //     })
        // })

        //每秒刷新时间
        var that = this;
        setInterval(function() {
            that.formatTime((day,hour,minute,second)=>{
                that.setData({
                    "overDay":day,
                    "overHour":hour,
                    "overMinute":minute,
                    "overSecond":second,
                })
            })
         }, 1000);
    },

    /** 关闭顶部通知 */
      closeMsg(){
        this.setData({ isHiddenMsg: true});
        clearInterval(interval);
      },
      
     /** 获取滚动条基本信息 */
      topScroll(){
        var that = this;
        var query = wx.createSelectorQuery();
        //选择id
        query.select('#mjltest').boundingClientRect()
        query.exec(function (res) {
          var length = res[0].width;
          var windowWidth = wx.getSystemInfoSync().windowWidth; // 屏幕宽度
    
          that.setData({
            length: length,
            windowWidth: windowWidth,
            space: windowWidth
          });
          that.scrollling(); // 第一个字消失后立即从右边出现
        });
      },
      /** 向左滚动 */
      scrollling: function () {
        var that = this;
        var length = that.data.length; //滚动文字的宽度
        var windowWidth = that.data.windowWidth; //屏幕宽度
        let interval = setInterval(function () {
          var maxscrollwidth = length + that.data.space;
          var left = that.data.distance;
          if (left < maxscrollwidth) { //判断是否滚动到最大宽度
            that.setData({
              distance: left + that.data.step
            })
          } else {
            that.setData({
              distance: 0 // 直接重新滚动
            });
            clearInterval(interval);
            that.scrollling();
          }
        }, that.data.interval);
      },

      swipclick:function(e){
        wx.navigateTo({
          url: '/pages/class/class'
        })
    },
    //获取报名人数接口
        getVisit:function(callback){
            wx.request({
                url: 'http://101.42.35.137:8080/indexVisit',
                header: {
                    'content-type': 'application/json'
                  },
                success:function(res){
                    callback(res.data);
                }
              })
        },
        //获取时间戳
        formatTime:function(callback) {//newDateTime
            var date = new Date()
            // var year = date.getFullYear();
            // var month = date.getMonth() + 1;
            // var day = date.getDate();
            // var hour = date.getHours();
            // var minute = date.getMinutes();
            // var second = date.getSeconds();
            //秒级时间戳
            var i = parseInt(date.getTime() / 1000);
            var t = this.data.overTime - i;
            var overDate = new Date(t);
            var allSecond = overDate.getTime();
            //天
            var overDay = parseInt(allSecond / (3600 * 24));
            //时
            var overHour = parseInt((allSecond - overDay * (3600 * 24)) / 3600);
            //分
            var overMinute = parseInt((allSecond - overDay * (3600 * 24) - overHour * 3600) / 60);
            //秒
            var overSecond = allSecond - overDay * (3600 * 24) - overHour * 3600 - overMinute * 60

            callback(overDay,overHour,overMinute,overSecond);
            // console.log(i)
            // console.log( year + "年" + month + "月" + day + "日" + hour + "时" + minute + "分" + second + "秒")
          }
    });
