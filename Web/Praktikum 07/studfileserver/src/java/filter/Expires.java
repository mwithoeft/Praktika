package filter;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Expires implements Filter {

    private Integer days = -1;

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        if (days > -1) {
            Calendar c = Calendar.getInstance();
            c.setTime(new Date());
            c.add(Calendar.DATE, days);
            
            //HTTP header date format: Thu, 01 Dec 1994 16:00:00 GMT
            String o = new SimpleDateFormat("EEE, d MMM yyyy HH:mm:ss zzz").format(c.getTime());
            String uri = ((HttpServletRequest) request).getRequestURI();
            
            ((HttpServletResponse) response).setHeader("Expires", o);
            if(uri.endsWith(".png")) {
                ((HttpServletResponse) response).setHeader("ContentType", "image/png");
            } else if (uri.endsWith(".mp4")) {
                ((HttpServletResponse) response).setHeader("ContentType", "video/mp4");
            }
            
        }

        chain.doFilter(request, response);
    }

    @Override
    public void init(FilterConfig filterConfig) {
        String expiresAfter = filterConfig.getInitParameter("days");
        if (expiresAfter != null) {
            try {
                days = Integer.parseInt(expiresAfter);
            } catch (NumberFormatException nfe) {
                //falsch konfiguriert
            }
        }
    }

    @Override
    public void destroy() {
    }
}
